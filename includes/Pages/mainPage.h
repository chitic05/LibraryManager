#pragma once
#include "page.h"

#include <iostream>
#include "Pages/pageManager.h"
#include "Pages/libraryPage.h"
class MainPage:public Page{
    public:
        MainPage();
        void Load() override;
        void initNeighbourPages() override;

};