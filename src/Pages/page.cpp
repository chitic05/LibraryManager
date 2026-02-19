#include "Pages/page.h"

// Empty destructor - pages don't delete neighbors (PageManager owns everything)
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