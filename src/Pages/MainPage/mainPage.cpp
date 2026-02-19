#include "Pages/MainPage/mainPage.h"
#include "Pages/pageManager.h"
#include <iostream>
#include <terminal.hpp>
MainPage::MainPage()
    :Page(){
    this->pageKey = "mainPage";
    this->pageName = "Main Page";
    this->text = "\tMain page\n"
                 "1. Library management\n"
                 "2. Patrons management\n"
                 "3. Operations\n"
                 "--Write the number that represents your pick and press enter--\n";
                 
}

void MainPage::initNeighbourPages(){
    this->previous = nullptr;
    this->next = {PageManager::getPage("libraryPage"), PageManager::getPage("patronsPage"), PageManager::getPage("operationsPage")};
}
void MainPage::Load(){
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    std::getline(std::cin, line);
    
    
    if(line[0] == '1')
        try{
            PageManager::changePage(this->next[0]);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the next page: "+ e.what() << '\n';
        }
    else if(line[0] == '2')
        try{
            PageManager::changePage(this->next[1]);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the next page: "+ e.what() << '\n';
        }
    else if(line[0] == '3')
        try{
            PageManager::changePage(this->next[2]);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the next page: "+ e.what() << '\n';
        }
    else
        keyError(line, this->pageKey);
}
