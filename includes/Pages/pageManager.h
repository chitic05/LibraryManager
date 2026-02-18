#pragma once

#include <memory>
#include "page.h"
class PageManager{
    public:
        static void changePage(Page* nextPage);
    private:
        static std::unique_ptr<Page> currentPage;
};