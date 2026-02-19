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
                 "--press B and enter to go back--\n";
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
    LibraryManager::displayBooks();
    
    // Check if there are any books to remove
    if(!LibraryManager::hasBooks()){
        std::cout << "No books available to remove.\n";
        std::cout << "--press enter to go back--\n";
        std::getline(std::cin, line);
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }
    
    std::cout << "Number of books to remove (type 0 and press enter to go back): ";
    std::getline(std::cin, countStr);
    if(onlyDigits(countStr)){
        count = std::stoi(countStr);
    }else if(countStr.length() == 1 && tolower(countStr[0]) == 'b'){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
    }else NaNError(countStr, this->pageKey);

    if(count == 0){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
    }else{
        for(uint i=0; i<count; ++i){
            std::string bookID;
            clearTerminal();
            std::cout << this->text;
            LibraryManager::displayBooks();
            std::cout << "Book " << i+1 << " of " << count << '\n';
            std::cout << "Enter Book ID to remove: ";
            std::getline(std::cin, bookID);

            if(bookID.length() == 1 && tolower(bookID[0]) == 'b'){
                try{
                    PageManager::changePage(this->previous);
                }catch(const std::exception& e){
                    std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
                }
            }

            if(onlyDigits(bookID)){
                LibraryManager::removeBook(bookID);
                
                // Check if there are any books left
                if(!LibraryManager::hasBooks()){
                    clearTerminal();
                    std::cout << "\tRemove Books\nNo more books in the library!\n";
                    std::cout << "--press enter to continue--\n";
                    std::getline(std::cin, line);
                    
                    try{
                        PageManager::changePage(this->previous);
                    }catch(const std::exception& e){
                        std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
                    }
                    return;
                }
            }else{
                std::cout << '\"' << bookID << "\" isn't a valid ID. Please enter the data again\n--To renter data for Book " << i+1 << " press enter--";
                --i;
                std::getline(std::cin, line);
            }
        }
    }
    
    clearTerminal();
    std::cout << "\tRemove Books\nBooks removed from the library!\n";
    std::cout << "--press enter to continue--\n";
    std::getline(std::cin, line);
    
    try{
        PageManager::changePage(this->previous);
    }catch(const std::exception& e){
        std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
    }
}
