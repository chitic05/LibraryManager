#include "Pages/pageManager.h"
#include "Pages/mainPage.h"
#include "terminal.hpp"
#include <iostream>

int main(){
    std::ios_base::sync_with_stdio(false);  // Faster I/O (i can't mix printf, cout, scanf, cin anymore)
    std::cout.setf(std::ios::unitbuf);      // Auto-flush to prevent buffering issues
    
    // Start application - PageManager owns all pages, handles navigation
    PageManager::changePage(PageManager::getPage("mainPage"));
    return 0;
}