#pragma once

#include "Pages/mainPage.h" // this also includes page.h

class LibraryPage:public Page{
    public:
        LibraryPage();
        void Load() override;
        void initNeighbourPages() override;
};