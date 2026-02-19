#pragma once

#include "Pages/page.h"
class OperationsPage:public Page{
    public:
        OperationsPage();
        void Load() override;
        void initNeighbourPages() override;
};
