#include "Pages/mainPage.h"

MainPage::MainPage()
    :Page(){
    this->pageName = "Main Page";
    this->text = "SELECT WHERE YOU WANT TO GO\n"
                 "1. Library management\n"
                 "2. Patrons management\n"
                 "--Write the number that represents your pick and press enter--\n";
}

void MainPage::initNeighbourPages(){
    this->previous = nullptr;
    this->next = {new LibraryPage};
}
void MainPage::Load(){
    initNeighbourPages();
    std::string line;
    std::cout << this->text;
    std::getline(std::cin, line);
    std::cout << std::string(50, '\n');
    if(line == "1")
        PageManager::changePage(this->next[0]);
}
