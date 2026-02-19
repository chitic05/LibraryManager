#include "Pages/pageManager.h"
#include "Pages/MainPage/mainPage.h"
#include "Pages/MainPage/LibraryPage/libraryPage.h"
#include "Pages/MainPage/LibraryPage/addBooksPage.h"
#include "Pages/MainPage/LibraryPage/removeBooksPage.h"
#include "Pages/MainPage/LibraryPage/updateBooksPage.h"
#include "Pages/MainPage/LibraryPage/listBooksPage.h"
#include "Pages/MainPage/PatronsPage/patronsPage.h"
#include "Pages/MainPage/PatronsPage/addPatronsPage.h"
#include "Pages/MainPage/PatronsPage/updatePatronsPage.h"
#include "Pages/MainPage/PatronsPage/removePatronsPage.h"
#include "Pages/MainPage/PatronsPage/listPatronsPage.h"
#include "Pages/MainPage/PatronsPage/checkoutBookPage.h"
#include "Pages/MainPage/PatronsPage/returnBookPage.h"
#include "Pages/MainPage/OperationsPage/operationsPage.h"
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
    pages["operationsPage"] = std::make_unique<OperationsPage>();
    pages["addBooksPage"] = std::make_unique<AddBooksPage>();
    pages["removeBooksPage"] = std::make_unique<RemoveBooksPage>();
    pages["updateBooksPage"] = std::make_unique<UpdateBooksPage>();
    pages["listBooksPage"] = std::make_unique<ListBooksPage>();
    pages["addPatronsPage"] = std::make_unique<AddPatronsPage>();
    pages["updatePatronsPage"] = std::make_unique<UpdatePatronsPage>();
    pages["removePatronsPage"] = std::make_unique<RemovePatronsPage>();
    pages["listPatronsPage"] = std::make_unique<ListPatronsPage>();
    pages["checkoutBookPage"] = std::make_unique<CheckoutBookPage>();
    pages["returnBookPage"] = std::make_unique<ReturnBookPage>();
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
