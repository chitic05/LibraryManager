#pragma once

#include "Pages/page.h"

class CheckoutBookPage:public Page{
    public:
        CheckoutBookPage();
        void Load() override;
        void initNeighbourPages() override;
};
