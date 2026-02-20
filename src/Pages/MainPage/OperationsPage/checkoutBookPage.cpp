#include "Pages/MainPage/OperationsPage/checkoutBookPage.h"
#include "Pages/pageManager.h"
#include "patron.h"
#include "library.h"
#include "terminal.hpp"
#include <iostream>

CheckoutBookPage::CheckoutBookPage()
    :Page(){
    this->pageKey = "checkoutBookPage";
    this->pageName = "Checkout Book Page";
    this->text = "\tCHECKOUT BOOK\n";
}

void CheckoutBookPage::initNeighbourPages(){
    this->previous = PageManager::getPage("operationsPage");
    this->next = {};
}

void CheckoutBookPage::Load(){
    initNeighbourPages();
    std::string countStr, line;
    uint count;
    
    clearTerminal();
    
    // Check if there are any patrons
    if(!PatronManager::hasPatrons()){
        std::cerr << "Error: No patrons in the database. Please add patrons first.\n";
        std::cout << "--press enter to continue--";
        std::getline(std::cin, line);
        changePage(this->previous);
        return;
    }
    
    // Check if there are any books
    if(!LibraryManager::hasBooks()){
        std::cerr << "Error: No books in the library. Please add books first.\n";
        std::cout << "--press enter to continue--";
        std::getline(std::cin, line);
        changePage(this->previous);
        return;
    }
    
    // Display all patrons
    PatronManager::displayPatrons();
    
    std::cout << this->text << std::flush;
    std::cout << "Enter Patron ID (or B to go back): ";
    std::getline(std::cin, line);
    
    if(tolower(line[0]) == 'b'){
        changePage(this->previous);
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
    
    // Display available books
    std::cout << "\nAvailable Books:\n";
    bool hasAvailableBooks = LibraryManager::displayBooks("status", "Available");
    
    if(!hasAvailableBooks){
        std::cout << "No books to borrow.\n";
        std::cout << "--press enter to go back--";
        std::getline(std::cin, line);
        changePage(this->previous);
        return;
    }
    
    std::cout << "Number of books to checkout (type 0 to go back): ";
    std::getline(std::cin, countStr);
    if(onlyDigits(countStr)){
        count = std::stoi(countStr);
    }else if(countStr.length() == 1 && tolower(countStr[0]) == 'b'){
        changePage(this->previous);
        return;
    }else{
        std::cout << '"' << countStr << "\" isn't a valid number. Please enter the data again\n--press enter to continue--";
        std::getline(std::cin, line);
        PageManager::changePage(PageManager::getPage(this->pageKey));
        return;
    }

    if(count == 0){
        changePage(this->previous);
        return;
    }else{
        for(uint i=0; i<count; ++i){
            std::string bookID;
            clearTerminal();
            std::cout << "\nAvailable Books:\n";
            bool hasAvailableBooks = LibraryManager::displayBooks("status", "Available");
            
            if(!hasAvailableBooks){
                std::cout << "No books to borrow.\n";
                std::cout << "--press enter to go back--";
                std::getline(std::cin, line);
                changePage(this->previous);
                return;
            }
            
            std::cout << "Book " << i+1 << " of " << count << '\n';
            std::cout << "Enter Book ID to checkout (write 0 to go back): ";
            std::getline(std::cin, bookID);
            
            if(bookID == "0"){
                changePage(this->previous);
                return;
            }

            if(bookID.length() == 1 && tolower(bookID[0]) == 'b'){
                changePage(this->previous);
                return;
            }

            if(onlyDigits(bookID)){
                bool success = PatronManager::checkoutBook(patronId, bookID);
                if(!success){
                    std::cout << '"' << bookID << "\" isn't a valid ID. Please enter the data again\n--To re-enter data for Book " << i+1 << " press enter--";
                    --i;  // retry this iteration
                    std::getline(std::cin, line);
                }
            }else{
                std::cout << '"' << bookID << "\" isn't a valid ID. Please enter the data again\n--To re-enter data for Book " << i+1 << " press enter--";
                --i;
                std::getline(std::cin, line);
            }
        }
        
        changePage(this->previous);
    }
}
