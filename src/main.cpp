#include "Pages/pageManager.h"
#include "terminal.hpp"
#include "library.h"
#include "patron.h"
#include <iostream>

int main(){
    std::ios_base::sync_with_stdio(false);  // Faster I/O (i can't mix printf, cout, scanf, cin anymore)
    std::cout.setf(std::ios::unitbuf);      // Auto-flush to prevent buffering issues
    LibraryManager::initDB();
    PatronManager::initDB();
    // Start application - PageManager owns all pages, handles navigation
    PageManager::changePage(PageManager::getPage("mainPage"));
    return 0;
}