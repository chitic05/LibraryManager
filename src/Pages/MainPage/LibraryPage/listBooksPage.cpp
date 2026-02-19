#include "Pages/MainPage/LibraryPage/listBooksPage.h"
#include "Pages/pageManager.h"
#include "library.h"
#include <iostream>
#include <terminal.hpp>

ListBooksPage::ListBooksPage()
    :Page(){
    this->pageKey = "listBooksPage";
    this->pageName = "List Books Page";
    this->text = "\tList Books\n"
                 "1. List all books\n"
                 "2. List by name\n"
                 "3. List by author\n"
                 "4. List by status\n"
                 "--Write the number that represents your pick and press enter--\n"
                 "--press B and enter to go back--\n";
}

void ListBooksPage::initNeighbourPages(){
    this->previous = PageManager::getPage("libraryPage");
}

void ListBooksPage::Load(){
    initNeighbourPages();
    std::string line;
    
    clearTerminal();
    std::cout << this->text;
    
    // Check if there are any books to list
    if(!LibraryManager::hasBooks()){
        std::cout << "No books available to list.\n";
        std::cout << "--press enter to go back--\n";
        std::getline(std::cin, line);
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }
    
    std::getline(std::cin, line);
    
    if(line.length() == 1 && tolower(line[0]) == 'b'){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }
    else if(line == "1"){
        clearTerminal();
        std::cout << this->text;
        LibraryManager::displayBooks("all");
        std::cout << "--press enter to continue--\n";
        std::getline(std::cin, line);
    }
    else if(line == "2"){
        clearTerminal();
        std::cout << this->text;
        std::cout << "Enter book name to search: ";
        std::string searchName;
        std::getline(std::cin, searchName);
        LibraryManager::displayBooks("name", searchName);
        std::cout << "--press enter to continue--\n";
        std::getline(std::cin, line);
    }
    else if(line == "3"){
        clearTerminal();
        std::cout << this->text;
        std::cout << "Enter author name to search: ";
        std::string searchAuthor;
        std::getline(std::cin, searchAuthor);
        LibraryManager::displayBooks("author", searchAuthor);
        std::cout << "--press enter to continue--\n";
        std::getline(std::cin, line);
    }
    else if(line == "4"){
        clearTerminal();
        std::cout << this->text;
        std::cout << "Enter status to filter:\n";
        std::cout << "1. Available\n";
        std::cout << "2. Borrowed\n";
        std::cout << "Enter choice: ";
        std::string statusChoice;
        std::getline(std::cin, statusChoice);
        
        std::string searchStatus;
        if(statusChoice == "1"){
            searchStatus = "Available";
        }else if(statusChoice == "2"){
            searchStatus = "Borrowed";
        }else{
            std::cout << '\"' << statusChoice << "\" isn't a valid choice.\n";
            std::cout << "--press enter to continue--";
            std::getline(std::cin, line);
            try{
                PageManager::changePage(PageManager::getPage(this->pageKey));
            }catch(const std::exception& e){
                std::cerr << this->getName() + " couldn't reload: "+ e.what() << '\n';
            }
            return;
        }
        
        LibraryManager::displayBooks("status", searchStatus);
        std::cout << "--press enter to continue--\n";
        std::getline(std::cin, line);
    }
    else{
        keyError(line, this->pageKey);
        return;
    }
    
    try{
        PageManager::changePage(this->previous);
    }catch(const std::exception& e){
        std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
    }
}
