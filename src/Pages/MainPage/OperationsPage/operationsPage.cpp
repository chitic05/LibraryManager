#include "Pages/MainPage/OperationsPage/operationsPage.h"
#include "Pages/pageManager.h"
#include <iostream>
#include <terminal.hpp>

OperationsPage::OperationsPage()
    :Page(){
    this->pageKey = "operationsPage";
    this->pageName = "Operations Page";
    this->text = "\tOPERATIONS\n"
                 "1. Checkout book\n"
                 "2. Return book\n"
                 "--Write the number that represents your pick and press enter--\n"
                 "--press B and enter anytime to go back--\n";
                 
}

void OperationsPage::initNeighbourPages(){
    this->previous = PageManager::getPage("mainPage");
    this->next = {
        PageManager::getPage("checkoutBookPage"),
        PageManager::getPage("returnBookPage")
    };
}

void OperationsPage::Load(){
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    std::getline(std::cin, line);
    if(line == "1"){
        try{
            PageManager::changePage(this->next[0]);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the checkout page: "+ e.what() << '\n';
        }
    }
    else if(line == "2"){
        try{
            PageManager::changePage(this->next[1]);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the return page: "+ e.what() << '\n';
        }
    }
    else if(tolower(line[0]) == 'b'){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
    }
    else
        keyError(line, this->pageKey);
}
