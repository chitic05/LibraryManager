#pragma once
#include "Pages/page.h"

class RemoveBooksPage:public Page{
    public:
        RemoveBooksPage();
        void Load() override;
        void initNeighbourPages() override;

};
