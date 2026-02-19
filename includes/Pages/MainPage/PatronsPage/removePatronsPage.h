#pragma once

#include "Pages/page.h"

class RemovePatronsPage:public Page{
    public:
        RemovePatronsPage();
        void Load() override;
        void initNeighbourPages() override;
};
