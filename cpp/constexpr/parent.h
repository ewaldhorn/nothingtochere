// Parent.h
#pragma once
class Parent {
    public:
       size_t getMoneyCount();
       constexpr Parent(const char *moneyString): mData(moneyString) {};
    private:
        std::string_view mData;     
};
extern Parent everyonesParent;
