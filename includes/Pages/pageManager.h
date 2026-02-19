#pragma once

#include <stdexcept>
#include <unordered_map>
#include <memory>
#include <string>
#include "page.h"
class PageManager{
    public:
        static void changePage(Page* nextPage);
        static Page* getPage(const std::string& pageName);
    private:
        static std::unordered_map<std::string, std::unique_ptr<Page>> allPages;
        static Page* currentPage;
};