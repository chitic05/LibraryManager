#include "Pages/libraryPage.h"

LibraryPage::LibraryPage(){
    this->pageName = "Library Page";
    this->text = "LIBRARY\n"
                "1.Add\n"
                "2.Update\n"
                "3.Remove\n"
                "4.List books\n"
                "--Write the number that represents your pick and press enter--\n";
}


void LibraryPage::initNeighbourPages(){
    this->previous = new MainPage();
}

void LibraryPage::Load(){
    std::string line;
    std::cout << this->text;
    std::getline(std::cin, line);
    std::cout << std::string(50, '\n');
}