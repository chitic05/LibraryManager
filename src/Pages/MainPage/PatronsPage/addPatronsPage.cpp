#include "Pages/MainPage/PatronsPage/addPatronsPage.h"
#include "Pages/pageManager.h"
#include "patron.h"
#include "terminal.hpp"
#include <iostream>

AddPatronsPage::AddPatronsPage()
    :Page(){
    this->pageKey = "addPatronsPage";
    this->pageName = "Add Patrons Page";
    this->text = "\tADD PATRONS\n"
                 "How many patrons do you want to add?\n"
                 "--Write a number and press enter--\n"
                 "--press B and enter anytime to go back--\n";
}

void AddPatronsPage::initNeighbourPages(){
    this->previous = PageManager::getPage("patronsPage");
    this->next = {};
}

void AddPatronsPage::Load(){
    initNeighbourPages();
    clearTerminal();
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
    
    if(!onlyDigits(line)){
        std::cout << '"' << line << "\" isn't a valid number. Please enter the data again\n--press enter to continue--";
        std::getline(std::cin, line);
        PageManager::changePage(PageManager::getPage(this->pageKey));
        return;
    }
    
    int numberOfPatrons = std::stoi(line);
    if(numberOfPatrons <= 0){
        std::cerr << "Error: Please enter a positive number\n";
        std::cout << "--press enter to continue--";
        std::getline(std::cin, line);
        PageManager::changePage(PageManager::getPage(this->pageKey));
        return;
    }
    
    clearTerminal();
    
    for(int i = 0; i < numberOfPatrons; i++){
        std::cout << "\n--- Patron " << (i + 1) << " ---\n";
        
        std::string name;
        std::cout << "Name: ";
        std::getline(std::cin, name);
        
        if(name.empty()){
            std::cout << "Name cannot be empty. Please enter the data again\n--To re-enter data for Patron " << i+1 << " press enter--";
            --i;
            std::getline(std::cin, line);
            continue;
        }
        
        PatronManager::addPatron(name);
    }
    
    std::cout << "\nAll patrons added successfully!\n";
    std::cout << "--press enter to continue--";
    std::getline(std::cin, line);
    
    try{
        PageManager::changePage(this->previous);
    }catch(const std::exception& e){
        std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
    }
}
