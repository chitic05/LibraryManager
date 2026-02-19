#pragma once
#include "Pages/page.h"

class AddBooksPage:public Page{
    public:
        AddBooksPage();
        void Load() override;
        void initNeighbourPages() override;

};