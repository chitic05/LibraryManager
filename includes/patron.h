#pragma once
#include "json.hpp"
using json = nlohmann::json;

class PatronManager{
    public:
        static void addPatron(std::string name);
        static void removePatron(std::string id);
        static void updatePatron(std::string id, std::string field, std::string value);
        static void displayPatrons(std::string filter = "all", std::string searchValue = "");
        static bool displayPatronBooks(std::string patronId);
        static bool hasPatrons();
        static bool checkoutBook(std::string patronId, std::string bookId);
        static bool returnBook(std::string patronId, std::string bookId);
        static json getPatronInfo(std::string id);
        static void initDB();
        static void saveChange();
        
    private:
        static std::string jsonPath;
        static json db;
        
};
