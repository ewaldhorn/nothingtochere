#include<iostream>
#include <random>

constexpr int add2(int input) {
    return input + 2;
}

int main() {
    int rd = std::rand();
    int b = add2(rd);
    std::cout << "b = " << b;
    return 0;
}