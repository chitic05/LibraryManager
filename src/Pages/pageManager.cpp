#include "Pages/pageManager.h"
#include "Pages/libraryPage.h"
#include "Pages/mainPage.h"
#include "Pages/patronsPage.h"
#include "terminal.hpp"
#include <stdexcept>

Page* PageManager::currentPage = nullptr;

// Registry pattern: Central storage owns all pages via unique_ptr for automatic memory management
// Lambda initializer used because unique_ptr can't be copied in initializer lists
std::unordered_map<std::string, std::unique_ptr<Page>> PageManager::allPages = [](){
    std::unordered_map<std::string, std::unique_ptr<Page>> pages;
    pages["mainPage"] = std::make_unique<MainPage>();
    pages["libraryPage"] = std::make_unique<LibraryPage>();
    pages["patronsPage"] = std::make_unique<PatronsPage>();
    return pages;
}();

void PageManager::changePage(Page* nextPage){
    clearTerminal();  // Clear before showing new page
    currentPage = nextPage;  // Non-owning pointer - just references page owned by allPages
    if(currentPage)
        currentPage->Load();
    else
        throw std::runtime_error("Page can't be loaded!");
}

Page* PageManager::getPage(const std::string& pageName){
    auto it = allPages.find(pageName);
    if(it != allPages.end())
        return it->second.get();  // .get() returns raw pointer without transferring ownership
    return nullptr;
}
