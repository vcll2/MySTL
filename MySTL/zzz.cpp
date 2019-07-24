#include "vector.h"
#include<iostream>

int main() {
    mystl::vector<int> myv(3, 100);
    for(auto ch : myv) {
        std::cout << ch << std::endl;
    }
}