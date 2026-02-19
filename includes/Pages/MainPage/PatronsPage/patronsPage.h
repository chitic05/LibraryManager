#pragma once

#include "Pages/page.h"
class PatronsPage:public Page{
    public:
        PatronsPage();
        void Load() override;
        void initNeighbourPages() override;
};