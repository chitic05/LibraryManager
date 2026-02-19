#include "library.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

// Initialize static members
std::string LibraryManager::jsonPath = "res/library.json";
json LibraryManager::db = json::object();

void LibraryManager::initDB(){
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << jsonPath << '\n';
        db = json::object();
        return;
    }
    try{
        db = json::parse(file);
    }catch(const std::exception& e){
        std::cerr << "JSON parse error: " << e.what() << '\n';
        db = json::object();
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
    // Check if maxID exists and is an integer
    if (!db.contains("maxID") || !db["maxID"].is_number_integer()) {
        std::cerr << "Error: maxID not found or invalid, initializing to 0\n";
        db["maxID"] = 0;
    }
    
    // Check if book already exists
    for (auto& [key, value] : db.items()) {
        if (key == "maxID") continue;  // Skip maxID entry
        
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
    
    // Get and increment maxID
    int newID = db["maxID"].get<int>() + 1;
    db["maxID"] = newID;
    
    // Create book entry using ID as key
    std::string idKey = std::to_string(newID);
    db[idKey] = {
        {"name", name},
        {"author", author},
        {"pubYear", pubYear},
        {"status", "Available"}
    };
    
    // Save to file
    saveChange();
}

void LibraryManager::removeBook(std::string id){
    // Check if the book exists
    if (!db.contains(id)) {
        std::cerr << "Error: Book with ID " << id << " not found\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Check if it's actually a book entry (not maxID)
    if (id == "maxID") {
        std::cerr << "Error: Cannot remove maxID entry\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Remove the book
    db.erase(id);
    
    // Save to file
    saveChange();
}

void LibraryManager::updateBook(std::string id, std::string field, std::string value){
    // Check if the book exists
    if (!db.contains(id)) {
        std::cerr << "Error: Book with ID " << id << " not found\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Check if it's actually a book entry (not maxID)
    if (id == "maxID") {
        std::cerr << "Error: Cannot update maxID entry\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Check if the book entry is an object
    if (!db[id].is_object()) {
        std::cerr << "Error: Invalid book entry\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Update the specified field
    db[id][field] = value;
    
    std::cout << "Book ID " << id << " updated successfully!\n";
    std::cout << "Press Enter to continue...";
    std::string l;
    std::getline(std::cin, l);
    
    // Save to file
    saveChange();
}

void LibraryManager::displayBooks(){
    std::cout << "\n========== LIBRARY BOOKS ==========\n";
    
    // Collect all books with their IDs
    std::vector<std::pair<std::string, json>> books;
    for (auto& [id, book] : db.items()) {
        if (id == "maxID") continue;
        if (book.is_object() && book.contains("name")) {
            books.push_back({id, book});
        }
    }
    
    if (books.empty()) {
        std::cout << "No books in the library.\n";
    } else {
        // Sort books alphabetically by name
        std::sort(books.begin(), books.end(), 
            [](const std::pair<std::string, json>& a, const std::pair<std::string, json>& b) {
                std::string nameA = a.second["name"];
                std::string nameB = b.second["name"];
                // Case-insensitive comparison
                std::transform(nameA.begin(), nameA.end(), nameA.begin(), ::tolower);
                std::transform(nameB.begin(), nameB.end(), nameB.begin(), ::tolower);
                return nameA < nameB;
            });
        
        // Display sorted books
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