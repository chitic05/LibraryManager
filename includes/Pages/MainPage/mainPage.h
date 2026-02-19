#pragma once
#include "Pages/page.h"
#include <iostream>
class MainPage:public Page{
    public:
        MainPage();
        void Load() override;
        void initNeighbourPages() override;

};