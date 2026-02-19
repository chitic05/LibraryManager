#include "Pages/libraryPage.h"
#include "Pages/pageManager.h"
#include <iostream>
#include "terminal.hpp"

LibraryPage::LibraryPage(){
    this->pageKey = "libraryPage";
    this->pageName = "Library Page";
    this->text = "\tLIBRARY\n"
                "1.Add book\n"
                "2.Update book\n"
                "3.Remove book\n"
                "4.List books\n"
                "--Write the number that represents your pick and press enter--\n"
                "--press B and enter to go back--\n";
}


void LibraryPage::initNeighbourPages(){
    this->previous = PageManager::getPage("mainPage");
}

void LibraryPage::Load(){
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    std::getline(std::cin, line);
    if(tolower(line[0]) == 'b'){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
    }
    else
        keyError(line, this->pageKey);

}