#include "Pages/MainPage/PatronsPage/patronsPage.h"
#include "Pages/pageManager.h"
#include <iostream>
#include <terminal.hpp>

PatronsPage::PatronsPage()
    :Page(){
    this->pageKey = "patronsPage";
    this->pageName = "Patrons Page";
    this->text = "\tPATRONS\n"
                 "1. Add patron\n"
                 "2. Update patron\n"
                 "3. Delete patron\n"
                 "4. List patrons\n"
                 "--Write the number that represents your pick and press enter--\n"
                 "--press B and enter to go back--\n";
                 
}

void PatronsPage::initNeighbourPages(){
    this->previous = PageManager::getPage("mainPage");
    this->next = {
        PageManager::getPage("addPatronsPage"),
        PageManager::getPage("updatePatronsPage"),
        PageManager::getPage("removePatronsPage"),
        PageManager::getPage("listPatronsPage")
    };
}

void PatronsPage::Load(){
    initNeighbourPages();
    std::string line;
    std::cout << this->text << std::flush;
    std::getline(std::cin, line);
    if(line == "1"){
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
