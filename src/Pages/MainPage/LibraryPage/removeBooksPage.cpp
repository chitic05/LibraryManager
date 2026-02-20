#include "Pages/MainPage/LibraryPage/removeBooksPage.h"
#include "Pages/pageManager.h"
#include "library.h"
#include <iostream>
#include <terminal.hpp>

RemoveBooksPage::RemoveBooksPage()
    :Page(){
    this->pageKey = "removeBooksPage";
    this->pageName = "Remove Books Page";
    this->text = "\tRemove Books\n"
                 "--press B and enter anytime to go back--\n";
}

void RemoveBooksPage::initNeighbourPages(){
    this->previous = PageManager::getPage("libraryPage");
}

void RemoveBooksPage::Load(){
    initNeighbourPages();
    std::string countStr, line;
    uint count;
    
    clearTerminal();
    std::cout << this->text;
    std::cout << "Available Books:\n";
    bool hasAvailableBooks = LibraryManager::displayBooks("status", "Available");
    
    // Check if there are any available books to remove
    if(!hasAvailableBooks){
        std::cout << "No available books to remove.\n";
        std::cout << "--press enter to go back--\n";
        std::getline(std::cin, line);
        changePage(this->previous);
        return;
    }
    
    std::cout << "Number of books to remove (type 0 and press enter to go back): ";
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
    }else{
        for(uint i=0; i<count; ++i){
            std::string bookID;
            clearTerminal();
            std::cout << this->text;
            std::cout << "Available Books:\n";
            bool hasAvailableBooks = LibraryManager::displayBooks("status", "Available");
            
            if(!hasAvailableBooks){
                std::cout << "No more available books to remove.\n";
                std::cout << "--press enter to go back--\n";
                std::getline(std::cin, line);
                changePage(this->previous);
                return;
            }
            
            std::cout << "Book " << i+1 << " of " << count << '\n';
            std::cout << "Enter Book ID to remove: ";
            std::getline(std::cin, bookID);

            if(bookID.length() == 1 && tolower(bookID[0]) == 'b'){
                changePage(this->previous);
                return;
            }

            if(onlyDigits(bookID)){
                LibraryManager::removeBook(bookID);
            }else{
                std::cout << '"' << bookID << "\" isn't a valid ID. Please enter the data again\n--To re-enter data for Book " << i+1 << " press enter--";
                --i;
                std::getline(std::cin, line);
            }
        }
    }
    
    clearTerminal();
    std::cout << "\tRemove Books\nBooks removed from the library!\n";
    std::cout << "--press enter to continue--\n";
    std::getline(std::cin, line);
    
    changePage(this->previous);
}
