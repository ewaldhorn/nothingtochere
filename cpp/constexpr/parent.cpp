// Parent.cpp
#include<Producer.h>

constinit static Parent everyonesParent("TheParent");

size_t Parent::getMoneyCount() {
    return mData.size();
}

//Child.cpp
#include<Child.h>

class Child {
    public:
    Child(Parent &parent) : mMoneyCount(parent.getMoneyCount()) {};
    private:
    size_t mMoneyCount;
};

static Child everyonesChild(everyonesParent);