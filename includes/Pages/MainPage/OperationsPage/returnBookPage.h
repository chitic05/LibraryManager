#pragma once

#include "Pages/page.h"

class ReturnBookPage:public Page{
    public:
        ReturnBookPage();
        void Load() override;
        void initNeighbourPages() override;
};
