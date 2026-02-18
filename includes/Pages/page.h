#pragma once
#include <string>
#include <memory>
#include <vector>

class Page{
    friend class PageManager;

    public:

        virtual void initNeighbourPages()=0;
        virtual void Load() = 0;
        virtual std::string getName();
        virtual Page* getPrevious();
        virtual ~Page();
    protected:
        std::string pageName;
        Page* previous;
        std::vector<Page*> next;
        std::string text;
};