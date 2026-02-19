#include "Pages/MainPage/PatronsPage/returnBookPage.h"
#include "Pages/pageManager.h"
#include "patron.h"
#include "library.h"
#include "terminal.hpp"
#include <iostream>

ReturnBookPage::ReturnBookPage()
    :Page(){
    this->pageKey = "returnBookPage";
    this->pageName = "Return Book Page";
    this->text = "\tRETURN BOOK\n";
}

void ReturnBookPage::initNeighbourPages(){
    this->previous = PageManager::getPage("operationsPage");
    this->next = {};
}

void ReturnBookPage::Load(){
    initNeighbourPages();
    std::string countStr, line;
    uint count;
    
    clearTerminal();
    
    // Check if there are any patrons
    if(!PatronManager::hasPatrons()){
        std::cerr << "Error: No patrons in the database.\n";
        std::cout << "--press enter to continue--";
        std::getline(std::cin, line);
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }
    
    // Display all patrons
    PatronManager::displayPatrons();
    
    std::cout << this->text << std::flush;
    std::cout << "Enter Patron ID (or B to go back): ";
    std::getline(std::cin, line);
    
    if(tolower(line[0]) == 'b'){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }
    
    if(!onlyDigits(line)){
        std::cout << '"' << line << "\" isn't a valid ID. Please enter the data again\n--press enter to continue--";
        std::getline(std::cin, line);
        PageManager::changePage(PageManager::getPage(this->pageKey));
        return;
    }
    
    std::string patronId = line;
    
    clearTerminal();
    
    // Display books checked out by this patron
    bool hasBooks = PatronManager::displayPatronBooks(patronId);
    
    if(!hasBooks){
        std::cout << "No books to return for this patron.\n";
        std::cout << "--press enter to go back--";
        std::getline(std::cin, line);
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }
    
    std::cout << "Number of books to return (type 0 to go back): ";;
    std::getline(std::cin, countStr);
    if(onlyDigits(countStr)){
        count = std::stoi(countStr);
    }else if(countStr.length() == 1 && tolower(countStr[0]) == 'b'){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }else{
        std::cout << '"' << countStr << "\" isn't a valid number. Please enter the data again\n--press enter to continue--";
        std::getline(std::cin, line);
        PageManager::changePage(PageManager::getPage(this->pageKey));
        return;
    }

    if(count == 0){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }else{
        for(uint i=0; i<count; ++i){
            std::string bookID;
            clearTerminal();
            bool hasBooks = PatronManager::displayPatronBooks(patronId);
            
            if(!hasBooks){
                std::cout << "No books to return for this patron.\n";
                std::cout << "--press enter to go back--";
                std::getline(std::cin, line);
                try{
                    PageManager::changePage(this->previous);
                }catch(const std::exception& e){
                    std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
                }
                return;
            }
            
            std::cout << "Book " << i+1 << " of " << count << '\n';
            std::cout << "Enter Book ID to return (write 0 to go back): ";
            std::getline(std::cin, bookID);
            
            if(bookID == "0"){
                try{
                    PageManager::changePage(this->previous);
                }catch(const std::exception& e){
                    std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
                }
                return;
            }

            if(bookID.length() == 1 && tolower(bookID[0]) == 'b'){
                try{
                    PageManager::changePage(this->previous);
                }catch(const std::exception& e){
                    std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
                }
                return;
            }

            if(onlyDigits(bookID)){
                bool success = PatronManager::returnBook(patronId, bookID);
                if(!success){
                    std::cout << '"' << bookID << "\" isn't a valid ID. Please enter the data again\n--To re-enter data for Book " << i+1 << " press enter--";
                    --i;
                    std::getline(std::cin, line);
                }
            }else{
                std::cout << '"' << bookID << "\" isn't a valid ID. Please enter the data again\n--To re-enter data for Book " << i+1 << " press enter--";
                --i;
                std::getline(std::cin, line);
            }
        }
        
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
    }
}
