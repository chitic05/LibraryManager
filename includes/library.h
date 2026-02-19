#pragma once
#include "json.hpp"
using json = nlohmann::json;

class LibraryManager{
    public:
        static void addBook(std::string name, std::string author, std::string pubYear);
        static void removeBook(std::string id);
        static void updateBook(std::string id, std::string field, std::string value);
        static void removeBooks();
        static void getBooks();
        static void displayBooks();
        static bool hasBooks();
        static void initDB();
        static void saveChange();
        
    private:
        static std::string jsonPath;
        static json db;
        
};