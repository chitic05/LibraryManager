#pragma once
#include <string>
#include <memory>
#include <vector>

// Forward declaration to break circular dependency (page.h ← → pageManager.h)
class PageManager;

class Page{
    friend class PageManager;

    public:

        virtual void initNeighbourPages()=0;
        virtual void Load() = 0;
        virtual std::string getName();
        virtual std::string getKey();
        virtual Page* getPrevious();
        virtual ~Page();
    protected:
        std::string pageName;  // Display name like "Main Page"
        std::string pageKey;   // Key in allPages map like "mainPage"
        Page* previous;        // Non-owning pointers - just references
        std::vector<Page*> next;
        std::string text;
};