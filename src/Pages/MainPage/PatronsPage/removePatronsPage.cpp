#include "Pages/MainPage/PatronsPage/removePatronsPage.h"
#include "Pages/pageManager.h"
#include "patron.h"
#include "terminal.hpp"
#include <iostream>

RemovePatronsPage::RemovePatronsPage()
    :Page(){
    this->pageKey = "removePatronsPage";
    this->pageName = "Remove Patrons Page";
    this->text = "\tREMOVE PATRONS\n";
}

void RemovePatronsPage::initNeighbourPages(){
    this->previous = PageManager::getPage("patronsPage");
    this->next = {};
}

void RemovePatronsPage::Load(){
    initNeighbourPages();
    std::string countStr, line;
    uint count;
    
    clearTerminal();
    std::cout << this->text;
    PatronManager::displayPatrons();
    
    // Check if there are any patrons
    if(!PatronManager::hasPatrons()){
        std::cout << "No patrons available to remove.\n";
        std::cout << "--press enter to go back--\n";
        std::getline(std::cin, line);
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
        return;
    }
    
    std::cout << "Number of patrons to remove (type 0 and press enter to go back): ";
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
            std::string patronID;
            clearTerminal();
            std::cout << this->text;
            PatronManager::displayPatrons();
            std::cout << "Patron " << i+1 << " of " << count << '\n';
            std::cout << "Enter Patron ID to remove: ";
            std::getline(std::cin, patronID);

            if(patronID.length() == 1 && tolower(patronID[0]) == 'b'){
                try{
                    PageManager::changePage(this->previous);
                }catch(const std::exception& e){
                    std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
                }
                return;
            }

            if(onlyDigits(patronID)){
                PatronManager::removePatron(patronID);
                
                // Check if there are any patrons left
                if(!PatronManager::hasPatrons()){
                    std::cout << "\nNo more patrons in the database.\n";
                    std::cout << "--press enter to go back--\n";
                    std::getline(std::cin, line);
                    try{
                        PageManager::changePage(this->previous);
                    }catch(const std::exception& e){
                        std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
                    }
                    return;
                }
            }else{
                std::cout << '"' << patronID << "\" isn't a valid ID. Please enter the data again\n--To re-enter data for Patron " << i+1 << " press enter--";
                --i;
                std::getline(std::cin, line);
            }
        }
        
        try{
            PageManager::changePage(this->previous);
        }catch(const std::exception& e){
            std::cerr << this->getName() + " couldn't load the previous page: "+ e.what() << '\n';
        }
    }
}
