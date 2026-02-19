#pragma once
#include "json.hpp"
using json = nlohmann::json;

class LibraryManager{
    public:
        static void addBook(std::string name, std::string author, std::string pubYear);
        static void removeBook(std::string id);
        static void updateBook(std::string id, std::string field, std::string value, bool silent = false);
        static void removeBooks();
        static void getBooks();
        static bool displayBooks(std::string filter = "all", std::string searchValue = "");
        static bool hasBooks();
        static json getBookInfo(std::string id);
        static void initDB();
        static void saveChange();
        
    private:
        static std::string jsonPath;
        static json db;
        
};