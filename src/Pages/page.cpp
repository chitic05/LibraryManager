#include "Pages/page.h"

Page::~Page(){
    delete previous;
    for(uint i = 0; i<next.size(); i++)
        delete next[i];
}

std::string Page::getName(){
    return this->pageName;
}

Page* Page::getPrevious(){
    return this->previous;
}