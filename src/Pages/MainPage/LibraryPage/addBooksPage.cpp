#include "Pages/MainPage/LibraryPage/addBooksPage.h"
#include "Pages/pageManager.h"
#include "library.h"
#include <iostream>
#include <terminal.hpp>

AddBooksPage::AddBooksPage()
    :Page(){
    this->pageKey = "addBooksPage";
    this->pageName = "Add Books Page";
    this->text = "\tAdd Books\n"
                 "--press B and enter to go back--\n";
}

void AddBooksPage::initNeighbourPages(){
    this->previous = PageManager::getPage("libraryPage");}
void AddBooksPage::Load(){
    initNeighbourPages();
    std::string countStr, line;
    uint count;
    std::cout << this->text;
    std::cout << "Number of books to add (type 0 and press enter to go back): ";
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

    if(count == 0 ){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
    }else{
        for(uint i=0; i<count; ++i){
            std::string name, author, pubYear;
            clearTerminal();
            std::cout << this->text;
            std::cout << "Book " << i+1 << '\n';
            for(uint j=0; j<3; ++j){
                std::string line;
                if(j==0)
                    std::cout << "Title: ";
                else if(j==1)
                    std::cout << "Author: ";
                else if(j==2)
                    std::cout << "Year of publication: ";
                std::getline(std::cin, line);

                 if(line.length() == 1 && tolower(line[0]) == 'b'){
                    try{
                        PageManager::changePage(this->previous);
                    }catch(const std::exception& e){
                        std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
                    }
                 }

                if(j==0)
                    name = line;
                else if(j==1)
                    author = line;
                else if(j==2){
                    if(onlyDigits(line)){
                        pubYear = line;
                        LibraryManager::addBook(name, author, pubYear);
                    }
                        
                    else{
                        std::cout << '\"' << line << "\" isn't an year. Please enter the data again\n--To renter data for Book " << i+1 << " press enter--";
                        --i;
                        std::getline(std::cin, line);
                    }
                }
                    
            }
        }
    }
    
    clearTerminal();
    std::cout << "\tAdd Books\nBooks added to the library!\n";
    std::cout << "--press enter to continue--\n";
    std::getline(std::cin, line);
    
    try{
        PageManager::changePage(this->previous);
    }catch(const std::exception& e){
        std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
    }
}

