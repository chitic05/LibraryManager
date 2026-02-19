#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
#include "Pages/pageManager.h"

// Cross-platform terminal clearing using ANSI escape codes (Linux) or cls (Windows)
inline void clearTerminal(){
    #ifdef _WIN32
        system("cls");
    #else
        std::cout << "\033[2J\033[H" << std::flush;  // \033[2J clears screen, \033[H moves cursor to top
    #endif
}

// Error handler: shows error message and reloads the current page
inline void keyError(std::string line, std::string pageKey){
    std::cout << "Error: Key \"" << line << "\" doesn't do anything" << std::endl;
    std::string b;
    std::getline(std::cin, b);
    
    try {
        PageManager::changePage(PageManager::getPage(pageKey)); // Reload this page
    } catch(const std::exception& e) {
        std::cerr << "Failed to reload page: " << e.what() << std::endl;
    }
}

inline void NaNError(std::string line, std::string pageKey){
    std::cout << "Error: \"" << line <<  "\" isn't a number" << std::endl;
    std::string b;
    std::getline(std::cin, b);
    
    try {
        PageManager::changePage(PageManager::getPage(pageKey)); // Reload this page
    } catch(const std::exception& e) {
        std::cerr << "Failed to reload page: " << e.what() << std::endl;
    }
}

// Check if string contains only digits (0-9)
inline bool onlyDigits(const std::string& str){
    if (str.empty()) return false;  // Empty string is not a valid number
    
    for (char ch : str) {
        if (ch < '0' || ch > '9') {
            return false;
        }
    }
    return true;
}