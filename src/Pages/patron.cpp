#include "patron.h"
#include "library.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

// Initialize static members
std::string PatronManager::jsonPath = "res/patrons.json";
json PatronManager::db = json::object();

void PatronManager::initDB(){
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << jsonPath << '\n';
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
        std::cerr << "JSON parse error: " << e.what() << '\n';
        db = json::object();
        db["maxID"] = 0;
        saveChange();
    }
}

void PatronManager::saveChange(){
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

void PatronManager::addPatron(std::string name){
    // Check if maxID exists and is an integer
    if (!db.contains("maxID") || !db["maxID"].is_number_integer()) {
        std::cerr << "Error: maxID not found or invalid, initializing to 0\n";
        db["maxID"] = 0;
    }
    
    // Check if patron already exists
    for (auto& [key, value] : db.items()) {
        if (key == "maxID") continue;
        
        if (value.is_object() && value.contains("name")) {
            if (value["name"] == name) {
                std::cerr << "Error: Patron already exists with ID " << key << "\n";
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
    
    // Create patron entry using ID as key
    std::string idKey = std::to_string(newID);
    db[idKey] = {
        {"name", name},
        {"booksCheckedOut", json::array()}
    };
    
    std::cout << "Patron added successfully with ID: " << newID << "\n";
    
    // Save to file
    saveChange();
}

void PatronManager::removePatron(std::string id){
    // Check if the patron exists
    if (!db.contains(id)) {
        std::cerr << "Error: Patron with ID " << id << " not found\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Check if it's actually a patron entry (not maxID)
    if (id == "maxID") {
        std::cerr << "Error: Cannot remove maxID entry\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Check if patron has books checked out
    if (db[id].is_object() && db[id].contains("booksCheckedOut")) {
        if (!db[id]["booksCheckedOut"].empty()) {
            std::cerr << "Error: Cannot delete patron with checked out books. Please return all books first.\n";
            std::cout << "Press Enter to continue...";
            std::string l;
            std::getline(std::cin, l);
            return;
        }
    }
    
    // Remove the patron
    db.erase(id);
    
    std::cout << "Patron removed successfully!\n";
    std::cout << "Press Enter to continue...";
    std::string l;
    std::getline(std::cin, l);
    
    // Save to file
    saveChange();
}

void PatronManager::updatePatron(std::string id, std::string field, std::string value){
    // Check if the patron exists
    if (!db.contains(id)) {
        std::cerr << "Error: Patron with ID " << id << " not found\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Check if it's actually a patron entry (not maxID)
    if (id == "maxID") {
        std::cerr << "Error: Cannot update maxID entry\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Check if the patron entry is an object
    if (!db[id].is_object()) {
        std::cerr << "Error: Invalid patron entry\n";
        std::cout << "Press Enter to continue...";
        std::string l;
        std::getline(std::cin, l);
        return;
    }
    
    // Update the specified field
    db[id][field] = value;
    
    std::cout << "Patron ID " << id << " updated successfully!\n";
    std::cout << "Press Enter to continue...";
    std::string l;
    std::getline(std::cin, l);
    
    // Save to file
    saveChange();
}

void PatronManager::displayPatrons(std::string filter, std::string searchValue){
    std::cout << "\n========== PATRONS ==========\n";
    
    // Collect all patrons with their IDs
    std::vector<std::pair<std::string, json>> patrons;
    for (auto& [id, patron] : db.items()) {
        if (id == "maxID") continue;
        if (patron.is_object() && patron.contains("name")) {
            // Apply filter
            bool include = true;
            if (filter == "name" && !searchValue.empty()) {
                std::string patronName = patron["name"];
                std::string searchLower = searchValue;
                std::string nameLower = patronName;
                std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
                std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
                include = (nameLower.find(searchLower) != std::string::npos);
            }
            
            if (include) {
                patrons.push_back({id, patron});
            }
        }
    }
    
    if (patrons.empty()) {
        std::cout << "No patrons found.\n";
    } else {
        // Sort patrons alphabetically by name
        std::sort(patrons.begin(), patrons.end(), 
            [](const std::pair<std::string, json>& a, const std::pair<std::string, json>& b) {
                std::string nameA = a.second["name"];
                std::string nameB = b.second["name"];
                // Case-insensitive comparison
                std::transform(nameA.begin(), nameA.end(), nameA.begin(), ::tolower);
                std::transform(nameB.begin(), nameB.end(), nameB.begin(), ::tolower);
                return nameA < nameB;
            });
        
        // Display sorted patrons
        for (const auto& [id, patron] : patrons) {
            std::cout << "ID: " << id;
            if (patron.contains("name")) std::cout << " | Name: " << patron["name"];
            if (patron.contains("booksCheckedOut")) {
                auto books = patron["booksCheckedOut"];
                std::cout << " | Books Checked Out: ";
                if (books.empty()) {
                    std::cout << "None";
                } else {
                    std::cout << "[";
                    for (size_t i = 0; i < books.size(); ++i) {
                        std::cout << books[i];
                        if (i < books.size() - 1) std::cout << ", ";
                    }
                    std::cout << "]";
                }
            }
            std::cout << "\n";
        }
    }
    std::cout << "=====================================\n\n";
}

bool PatronManager::hasPatrons(){
    for (auto& [id, patron] : db.items()) {
        if (id == "maxID") continue;
        if (patron.is_object()) {
            return true;
        }
    }
    return false;
}

bool PatronManager::checkoutBook(std::string patronId, std::string bookId){
    // Check if patron exists
    if (!db.contains(patronId) || patronId == "maxID") {
        return false;
    }
    
    // Check if book exists in library
    json bookInfo = LibraryManager::getBookInfo(bookId);
    if (bookInfo.empty()) {
        return false;
    }
    
    // Check if book is available
    if (bookInfo.contains("status") && bookInfo["status"] == "Borrowed") {
        return false;
    }
    
    // Add book to patron's checked out list
    if (!db[patronId].contains("booksCheckedOut")) {
        db[patronId]["booksCheckedOut"] = json::array();
    }
    
    // Check if book is already checked out by this patron
    for (auto& bookIdInList : db[patronId]["booksCheckedOut"]) {
        if (bookIdInList == bookId) {
            return false;
        }
    }
    
    // Add book ID to patron's list
    db[patronId]["booksCheckedOut"].push_back(bookId);
    
    // Update book status to "Borrowed" (silent mode)
    LibraryManager::updateBook(bookId, "status", "Borrowed", true);
    
    std::cout << "Book ID " << bookId << " checked out successfully to Patron ID " << patronId << "\n";
    std::cout << "Press Enter to continue...";
    std::string l;
    std::getline(std::cin, l);
    
    // Save changes
    saveChange();
    return true;
}

bool PatronManager::returnBook(std::string patronId, std::string bookId){
    // Check if patron exists
    if (!db.contains(patronId) || patronId == "maxID") {
        return false;
    }
    
    // Check if patron has books checked out
    if (!db[patronId].contains("booksCheckedOut") || db[patronId]["booksCheckedOut"].empty()) {
        return false;
    }
    
    // Find and remove book from patron's list
    auto& books = db[patronId]["booksCheckedOut"];
    bool found = false;
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i] == bookId) {
            books.erase(books.begin() + i);
            found = true;
            break;
        }
    }
    
    if (!found) {
        return false;
    }
    
    // Update book status to "Available" (silent mode)
    LibraryManager::updateBook(bookId, "status", "Available", true);
    
    std::cout << "Book ID " << bookId << " returned successfully by Patron ID " << patronId << "\n";
    std::cout << "Press Enter to continue...";
    std::string l;
    std::getline(std::cin, l);
    
    // Save changes
    saveChange();
    return true;
}

bool PatronManager::displayPatronBooks(std::string patronId){
    // Check if patron exists
    if (!db.contains(patronId) || patronId == "maxID") {
        std::cerr << "Error: Patron with ID " << patronId << " not found\n";
        return false;
    }
    
    // Check if patron has books checked out
    if (!db[patronId].contains("booksCheckedOut") || db[patronId]["booksCheckedOut"].empty()) {
        std::cout << "This patron has no books checked out.\n";
        return false;
    }
    
    std::cout << "\n========== BOOKS CHECKED OUT BY PATRON " << patronId << " ==========\n";
    
    // Get the list of book IDs checked out by this patron
    auto& bookIds = db[patronId]["booksCheckedOut"];
    
    // Display each book's details by looking it up in the library
    for (const auto& bookId : bookIds) {
        std::string id = bookId;
        json bookInfo = LibraryManager::getBookInfo(id);
        
        if (!bookInfo.empty()) {
            std::cout << "ID: " << id;
            if (bookInfo.contains("name")) std::cout << " | Title: " << bookInfo["name"];
            if (bookInfo.contains("author")) std::cout << " | Author: " << bookInfo["author"];
            if (bookInfo.contains("pubYear")) std::cout << " | Year: " << bookInfo["pubYear"];
            std::cout << "\n";
        } else {
            std::cout << "Book ID: " << id << " (details not found)\n";
        }
    }
    
    std::cout << "====================================================\n\n";
    return true;
}
