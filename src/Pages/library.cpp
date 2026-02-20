#include "library.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <filesystem>

std::string LibraryManager::jsonPath = "res/library.json";
json LibraryManager::db = json::object();

void LibraryManager::initDB(){
    namespace fs = std::filesystem;
    
    fs::path filePath(jsonPath);
    fs::path dirPath = filePath.parent_path();
    
    if (!dirPath.empty() && !fs::exists(dirPath)) {
        try {
            fs::create_directories(dirPath);
            std::cout << "Created directory: " << dirPath << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Failed to create directory " << dirPath << ": " << e.what() << "\n";
        }
    }
    
    if (!fs::exists(jsonPath)) {
        std::cout << "File " << jsonPath << " doesn't exist. Creating new file...\n";
        db = json::object();
        db["maxID"] = 0;
        saveChange();
        return;
    }
    
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << jsonPath << "\n";
        db = json::object();
        db["maxID"] = 0;
        saveChange();
        return;
    }
    try{
        db = json::parse(file);
        if (!db.contains("maxID")) {
            db["maxID"] = 0;
            saveChange();
        }
    }catch(const std::exception& e){
        std::cerr << "JSON parse error: " << e.what() << "\n";
        db = json::object();
        db["maxID"] = 0;
        saveChange();
    }
}

void LibraryManager::saveChange(){
    std::ofstream out(jsonPath);
    if (!out.is_open()) {
        std::cerr << "Failed to open " << jsonPath << " for writing\n";
        return;
    }
    out << db;
    out.close();
    if(out.fail()) {
        std::cerr << "Failed to write to " << jsonPath << '\n';
    }
}

void LibraryManager::addBook(std::string name, std::string author, std::string pubYear){
    if (!db.contains("maxID") || !db["maxID"].is_number_integer()) {
        std::cerr << "Error: maxID not found or invalid, initializing to 0\n";
        db["maxID"] = 0;
    }
    
    // Check duplicates
    for (auto& [key, value] : db.items()) {
        if (key == "maxID") continue;
        
        if (value.is_object() && 
            value.contains("name") && value.contains("author") && value.contains("pubYear")) {
            if (value["name"] == name && 
                value["author"] == author && 
                value["pubYear"] == pubYear) {
                std::cerr << "Error: Book already exists with ID " << key << "\n";
                std::cout << "--press enter to continue--";
                std::string l;
                std::getline(std::cin, l);
                return;
            }
        }
    }
    
    int newID = db["maxID"].get<int>() + 1;
    db["maxID"] = newID;
    
    std::string idKey = std::to_string(newID);
    db[idKey] = {
        {"name", name},
        {"author", author},
        {"pubYear", pubYear},
        {"status", "Available"}
    };
    
    saveChange();
}

void LibraryManager::removeBook(std::string id){
    if (!db.contains(id)) {
        std::cerr << "Error: Book with ID " << id << " not found\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    if (id == "maxID") {
        std::cerr << "Error: Cannot remove maxID entry\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Can't delete borrowed books
    if (db[id].is_object() && db[id].contains("status")) {
        if (db[id]["status"] == "Borrowed") {
            std::cerr << "Error: Cannot delete a borrowed book. Please return it first.\n";
            std::cout << "Press Enter to continue...";
            std::string l;
            std::getline(std::cin, l);
            return;
        }
    }
    
    db.erase(id);
    
    std::cout << "Book removed successfully!\n";
    std::cout << "Press Enter to continue...";
    std::string l;
    std::getline(std::cin, l);
    
    saveChange();
}

void LibraryManager::updateBook(std::string id, std::string field, std::string value, bool silent){
    if (!db.contains(id)) {
        if (!silent) {
            std::cerr << "Error: Book with ID " << id << " not found\n";
            std::cout << "Press Enter to continue...";
            std::string l;
            std::getline(std::cin, l);
        }
        return;
    }
    
    if (id == "maxID") {
        if (!silent) {
            std::cerr << "Error: Cannot update maxID entry\n";
            std::cout << "Press Enter to continue...";
            std::string l;
            std::getline(std::cin, l);
        }
        return;
    }
    
    if (!db[id].is_object()) {
        if (!silent) {
            std::cerr << "Error: Invalid book entry\n";
            std::cout << "Press Enter to continue...";
            std::string l;
            std::getline(std::cin, l);
        }
        return;
    }
    
    db[id][field] = value;
    
    if (!silent) {
        std::cout << "Book ID " << id << " updated successfully!\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
    }
    
    saveChange();
}

bool LibraryManager::displayBooks(std::string filter, std::string searchValue){
    std::cout << "\n========== LIBRARY BOOKS ==========\n";
    
    std::vector<std::pair<std::string, json>> books;
    for (auto& [id, book] : db.items()) {
        if (id == "maxID") continue;
        if (book.is_object() && book.contains("name")) {
            bool include = true;
            
            if (filter == "all") {
                include = true;
            } else if (filter == "name" && !searchValue.empty()) {
                std::string bookName = book["name"];
                std::string searchLower = searchValue;
                std::string nameLower = bookName;
                std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
                std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
                include = (nameLower.find(searchLower) != std::string::npos);
            } else if (filter == "author" && !searchValue.empty()) {
                if (book.contains("author")) {
                    std::string bookAuthor = book["author"];
                    std::string searchLower = searchValue;
                    std::string authorLower = bookAuthor;
                    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
                    std::transform(authorLower.begin(), authorLower.end(), authorLower.begin(), ::tolower);
                    include = (authorLower.find(searchLower) != std::string::npos);
                } else {
                    include = false;
                }
            } else if (filter == "status" && !searchValue.empty()) {
                if (book.contains("status")) {
                    std::string bookStatus = book["status"];
                    include = (bookStatus == searchValue);
                } else {
                    include = false;
                }
            }
            
            if (include) {
                books.push_back({id, book});
            }
        }
    }
    
    bool hasBooks = !books.empty();
    
    if (books.empty()) {
        std::cout << "No books found.\n";
    } else {
        // Sort by name
        std::sort(books.begin(), books.end(), 
            [](const std::pair<std::string, json>& a, const std::pair<std::string, json>& b) {
                std::string nameA = a.second["name"];
                std::string nameB = b.second["name"];
                std::transform(nameA.begin(), nameA.end(), nameA.begin(), ::tolower);
                std::transform(nameB.begin(), nameB.end(), nameB.begin(), ::tolower);
                return nameA < nameB;
            });
        
        for (const auto& [id, book] : books) {
            std::cout << "ID: " << id;
            if (book.contains("name")) std::cout << " | Title: " << book["name"];
            if (book.contains("author")) std::cout << " | Author: " << book["author"];
            if (book.contains("pubYear")) std::cout << " | Year: " << book["pubYear"];
            if (book.contains("status")) std::cout << " | Status: " << book["status"];
            std::cout << "\n";
        }
    }
    std::cout << "===================================\n\n";
    return hasBooks;
}

bool LibraryManager::hasBooks(){
    for (auto& [id, book] : db.items()) {
        if (id == "maxID") continue;
        if (book.is_object()) {
            return true;
        }
    }
    return false;
}

json LibraryManager::getBookInfo(std::string id){
    if (db.contains(id) && id != "maxID" && db[id].is_object()) {
        return db[id];
    }
    return json::object();
}