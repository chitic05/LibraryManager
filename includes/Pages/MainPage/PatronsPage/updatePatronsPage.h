#pragma once

#include "Pages/page.h"

class UpdatePatronsPage:public Page{
    public:
        UpdatePatronsPage();
        void Load() override;
        void initNeighbourPages() override;
};
