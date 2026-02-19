#pragma once

#include "Pages/page.h"

class ListPatronsPage:public Page{
    public:
        ListPatronsPage();
        void Load() override;
        void initNeighbourPages() override;
};
