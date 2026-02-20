#include "Pages/page.h"
#include "Pages/pageManager.h"
#include <iostream>

Page::~Page(){
}

std::string Page::getName(){
    return this->pageName;
}

std::string Page::getKey(){
    return this->pageKey;
}

Page* Page::getPrevious(){
    return this->previous;
}

void Page::changePage(Page* page){
    try{
        PageManager::changePage(page);
    }catch(const std::exception& e){
        std::cerr << this->getName() + " couldn't load the page: "+ e.what() << '\n';
    }
}