#pragma once
#include "Pages/page.h"

class ListBooksPage:public Page{
    public:
        ListBooksPage();
        void Load() override;
        void initNeighbourPages() override;

};
