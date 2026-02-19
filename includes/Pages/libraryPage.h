#pragma once

#include "Pages/page.h"
class LibraryPage:public Page{
    public:
        LibraryPage();
        void Load() override;
        void initNeighbourPages() override;
};