#include "Pages/MainPage/PatronsPage/listPatronsPage.h"
#include "Pages/pageManager.h"
#include "patron.h"
#include "terminal.hpp"
#include <iostream>

ListPatronsPage::ListPatronsPage()
    :Page(){
    this->pageKey = "listPatronsPage";
    this->pageName = "List Patrons Page";
    this->text = "\tLIST PATRONS\n"
                 "1. List all patrons\n"
                 "2. Search by name\n"
                 "--Write the number that represents your pick and press enter--\n"
                 "--press B and enter anytime to go back--\n";
}

void ListPatronsPage::initNeighbourPages(){
    this->previous = PageManager::getPage("patronsPage");
    this->next = {};
}

void ListPatronsPage::Load(){
    initNeighbourPages();
    clearTerminal();
    
    // Check if there are any patrons
    if(!PatronManager::hasPatrons()){
        std::cerr << "Error: No patrons in the database.\n";
        std::cout << "--press enter to continue--";
        std::string line;
        std::getline(std::cin, line);
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }
    
    std::string line;
    std::cout << this->text << std::flush;
    std::getline(std::cin, line);
    
    if(tolower(line[0]) == 'b'){
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }
    
    clearTerminal();
    
    if(line == "1"){
        // List all patrons
        PatronManager::displayPatrons();
    }
    else if(line == "2"){
        // Search by name
        std::cout << "Enter patron name to search: ";
        std::string searchName;
        std::getline(std::cin, searchName);
        
        if(searchName.empty()){
            std::cerr << "Error: Search term cannot be empty\n";
            std::cout << "--press enter to continue--";
            std::getline(std::cin, line);
            PageManager::changePage(PageManager::getPage(this->pageKey));
            return;
        }
        
        PatronManager::displayPatrons("name", searchName);
    }
    else {
        keyError(line, this->pageKey);
        return;
    }
    
    std::cout << "--press enter to continue--";
    std::getline(std::cin, line);
    
    try{
        PageManager::changePage(this->previous);
    }catch(const std::exception& e){
        std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
    }
}
