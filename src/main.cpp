#include "Pages/pageManager.h"
#include "Pages/mainPage.h"
int main(){

    MainPage* main = new MainPage();
    PageManager::changePage(main);

    return 0;
}