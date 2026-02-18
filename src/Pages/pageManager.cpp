#include "Pages/pageManager.h"
#include <stdexcept>
std::unique_ptr<Page> PageManager::currentPage = nullptr;

void PageManager::changePage(Page* nextPage){
    currentPage = std::move(std::unique_ptr<Page>(nextPage));
    if(currentPage)
        currentPage->Load();
    else
        throw std::runtime_error("Page can't be loaded!");
}
