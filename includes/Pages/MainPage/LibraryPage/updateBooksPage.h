#pragma once
#include "Pages/page.h"

class UpdateBooksPage:public Page{
    public:
        UpdateBooksPage();
        void Load() override;
        void initNeighbourPages() override;

};
