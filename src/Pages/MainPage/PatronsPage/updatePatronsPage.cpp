#include "Pages/MainPage/PatronsPage/updatePatronsPage.h"
#include "Pages/pageManager.h"
#include "patron.h"
#include "terminal.hpp"
#include <iostream>

UpdatePatronsPage::UpdatePatronsPage()
    :Page(){
    this->pageKey = "updatePatronsPage";
    this->pageName = "Update Patrons Page";
    this->text = "\tUPDATE PATRONS\n";
}

void UpdatePatronsPage::initNeighbourPages(){
    this->previous = PageManager::getPage("patronsPage");
    this->next = {};
}

void UpdatePatronsPage::Load(){
    initNeighbourPages();
    std::string countStr, line;
    uint count;
    
    clearTerminal();
    std::cout << this->text;
    PatronManager::displayPatrons();
    
    // Check if there are any patrons
    if(!PatronManager::hasPatrons()){
        std::cout << "No patrons available to update.\n";
        std::cout << "--press enter to go back--\n";
        std::getline(std::cin, line);
        changePage(this->previous);
        return;
    }
    
    std::cout << "Number of patrons to update (type 0 and press enter to go back): ";
    std::getline(std::cin, countStr);
    if(onlyDigits(countStr)){
        count = std::stoi(countStr);
    }else if(countStr.length() == 1 && tolower(countStr[0]) == 'b'){
        changePage(this->previous);
        return;
    }else{
        std::cout << '"' << countStr << "\" isn't a valid number. Please enter the data again\n--press enter to continue--";
        std::getline(std::cin, line);
        PageManager::changePage(PageManager::getPage(this->pageKey));
        return;
    }

    if(count == 0){
        changePage(this->previous);
        return;
    }else{
        for(uint i=0; i<count; ++i){
            std::string patronID;
            clearTerminal();
            std::cout << this->text;
            PatronManager::displayPatrons();
            std::cout << "Patron " << i+1 << " of " << count << '\n';
            std::cout << "Enter Patron ID to update: ";
            std::getline(std::cin, patronID);

            if(patronID.length() == 1 && tolower(patronID[0]) == 'b'){
                changePage(this->previous);
                return;
            }

            if(onlyDigits(patronID)){
                // Check if patron exists
                json patronInfo = PatronManager::getPatronInfo(patronID);
                if(patronInfo.empty()){
                    std::cout << "Error: Patron with ID " << patronID << " doesn't exist.\n";
                    std::cout << "--To re-enter data for Patron " << i+1 << " press enter--";
                    --i;
                    std::getline(std::cin, line);
                    continue;
                }
                
                // Update menu
                clearTerminal();
                std::cout << this->text;
                std::cout << "What would you like to update for Patron ID " << patronID << "?\n";
                std::cout << "1. Name\n";
                std::cout << "Enter choice: ";
                std::getline(std::cin, line);

                if(line == "1"){
                    std::cout << "Enter new name: ";
                    std::string newName;
                    std::getline(std::cin, newName);
                    if(!newName.empty()){
                        PatronManager::updatePatron(patronID, "name", newName);
                    }else{
                        std::cout << "Name cannot be empty. Please enter the data again\n--To re-enter data for Patron " << i+1 << " press enter--";
                        --i;
                        std::getline(std::cin, line);
                    }
                }else{
                    std::cout << "Invalid choice. Please enter the data again\n--To re-enter data for Patron " << i+1 << " press enter--";
                    --i;
                    std::getline(std::cin, line);
                }
            }else{
                std::cout << '"' << patronID << "\" isn't a valid ID. Please enter the data again\n--To re-enter data for Patron " << i+1 << " press enter--";
                --i;
                std::getline(std::cin, line);
            }
        }
        
        changePage(this->previous);
    }
}
