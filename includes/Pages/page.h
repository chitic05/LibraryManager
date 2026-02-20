#pragma once
#include <string>
#include <memory>
#include <vector>

class PageManager;

class Page{
    friend class PageManager;

    public:

        virtual void initNeighbourPages()=0;
        virtual void Load() = 0;
        virtual std::string getName();
        virtual std::string getKey();
        virtual Page* getPrevious();
        void changePage(Page* page);
        virtual ~Page();
    protected:
        std::string pageName;
        std::string pageKey;
        Page* previous;
        std::vector<Page*> next;
        std::string text;
};