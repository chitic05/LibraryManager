#include "Pages/MainPage/LibraryPage/updateBooksPage.h"
#include "Pages/pageManager.h"
#include "library.h"
#include <iostream>
#include <terminal.hpp>

UpdateBooksPage::UpdateBooksPage()
    :Page(){
    this->pageKey = "updateBooksPage";
    this->pageName = "Update Books Page";
    this->text = "\tUpdate Books\n"
                 "--press B and enter to go back--\n";
}

void UpdateBooksPage::initNeighbourPages(){
    this->previous = PageManager::getPage("libraryPage");
}

void UpdateBooksPage::Load(){
    initNeighbourPages();
    std::string countStr, line;
    uint count;
    
    clearTerminal();
    std::cout << this->text;
    LibraryManager::displayBooks();
    
    // Check if there are any books to update
    if(!LibraryManager::hasBooks()){
        std::cout << "No books available to update.\n";
        std::cout << "--press enter to go back--\n";
        std::getline(std::cin, line);
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }
    
    std::cout << "Number of books to update (type 0 and press enter to go back): ";
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
            std::cout << this->text;
            LibraryManager::displayBooks();
            std::cout << "Book " << i+1 << " of " << count << '\n';
            std::cout << "Enter Book ID to update: ";
            std::getline(std::cin, bookID);

            if(bookID.length() == 1 && tolower(bookID[0]) == 'b'){
                try{
                    PageManager::changePage(this->previous);
                }catch(const std::exception& e){
                    std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
                }
                return;
            }

            if(onlyDigits(bookID)){
                // Update menu
                clearTerminal();
                std::cout << this->text;
                std::cout << "What would you like to update for Book ID " << bookID << "?\n";
                std::cout << "1. Title\n";
                std::cout << "2. Author\n";
                std::cout << "3. Year of publication\n";
                std::cout << "4. Status\n";
                std::cout << "Enter choice: ";
                std::getline(std::cin, line);

                if(line == "1"){
                    std::cout << "Enter new title: ";
                    std::string newTitle;
                    std::getline(std::cin, newTitle);
                    LibraryManager::updateBook(bookID, "name", newTitle);
                }else if(line == "2"){
                    std::cout << "Enter new author: ";
                    std::string newAuthor;
                    std::getline(std::cin, newAuthor);
                    LibraryManager::updateBook(bookID, "author", newAuthor);
                }else if(line == "3"){
                    std::cout << "Enter new year of publication: ";
                    std::string newYear;
                    std::getline(std::cin, newYear);
                    if(onlyDigits(newYear)){
                        LibraryManager::updateBook(bookID, "pubYear", newYear);
                    }else{
                        std::cout << '\"' << newYear << "\" isn't a valid year. Update cancelled.\n";
                        std::cout << "--press enter to continue--";
                        std::getline(std::cin, line);
                        --i;
                    }
                }else if(line == "4"){
                    std::cout << "Enter new status:\n";
                    std::cout << "1. Available\n";
                    std::cout << "2. Borrowed\n";
                    std::cout << "Enter choice: ";
                    std::string statusChoice;
                    std::getline(std::cin, statusChoice);
                    if(statusChoice == "1"){
                        LibraryManager::updateBook(bookID, "status", "Available");
                    }else if(statusChoice == "2"){
                        LibraryManager::updateBook(bookID, "status", "Borrowed");
                    }else{
                        std::cout << '\"' << statusChoice << "\" isn't a valid choice. Update cancelled.\n";
                        std::cout << "--press enter to continue--";
                        std::getline(std::cin, line);
                        --i;
                    }
                }else{
                    std::cout << '\"' << line << "\" isn't a valid choice. Update cancelled.\n";
                    std::cout << "--press enter to continue--";
                    std::getline(std::cin, line);
                    --i;
                }
                
                // Check if there are any books left (in case something went wrong)
                if(!LibraryManager::hasBooks()){
                    clearTerminal();
                    std::cout << "\tUpdate Books\nNo more books in the library!\n";
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
                std::cout << '"' << bookID << "\" isn't a valid ID. Please enter the data again\n--To re-enter data for Book " << i+1 << " press enter--";
                --i;
                std::getline(std::cin, line);
            }
        }
    }
    
    clearTerminal();
    std::cout << "\tUpdate Books\nBooks updated in the library!\n";
    std::cout << "--press enter to continue--\n";
    std::getline(std::cin, line);
    
    try{
        PageManager::changePage(this->previous);
    }catch(const std::exception& e){
        std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
    }
}
