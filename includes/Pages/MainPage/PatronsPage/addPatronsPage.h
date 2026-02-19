#pragma once

#include "Pages/page.h"

class AddPatronsPage:public Page{
    public:
        AddPatronsPage();
        void Load() override;
        void initNeighbourPages() override;
};
