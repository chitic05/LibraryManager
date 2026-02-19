#include "Pages/MainPage/LibraryPage/libraryPage.h"
#include "Pages/pageManager.h"
#include <iostream>
#include <terminal.hpp>
LibraryPage::LibraryPage(){
    this->pageKey = "libraryPage";
    this->pageName = "Library Page";
    this->text = "\tLIBRARY\n"
                "1.Add books\n"
                "2.Update book\n"
                "3.Remove books\n"
                "4.List books\n"
                "--Write the number that represents your pick and press enter--\n"
                "--press B and enter to go back--\n";
}


void LibraryPage::initNeighbourPages(){
    this->previous = PageManager::getPage("mainPage");
    this->next = {PageManager::getPage("addBooksPage"), PageManager::getPage("updateBooksPage"), PageManager::getPage("removeBooksPage"), PageManager::getPage("listBooksPage")};
}

void LibraryPage::Load(){
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    std::getline(std::cin, line);
    if(line.length() == 1 && tolower(line[0]) == 'b'){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
    }
    else if(line == "1"){
        try{
            PageManager::changePage(this->next[0]);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the add page: "+ e.what() << '\n';
        }
    }
    else if(line == "2"){
        try{
            PageManager::changePage(this->next[1]);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the update page: "+ e.what() << '\n';
        }
    }
    else if(line == "3"){
        try{
            PageManager::changePage(this->next[2]);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the remove page: "+ e.what() << '\n';
        }
    }
    else if(line == "4"){
        try{
            PageManager::changePage(this->next[3]);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the list page: "+ e.what() << '\n';
        }
    }
    else
        keyError(line, this->pageKey);

}