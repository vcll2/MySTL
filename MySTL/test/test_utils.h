#ifndef __MYSTL_TEST_UTILS_H
#define __MYSTL_TEST_UTILS_H

#include<iterator>
#include<iostream>
#include<string>

namespace mystl {
namespace Test {
template<class Container>
void print_container(Container& container, const std::string& name = "") {
    std::cout << "Container " << name << " :";
    for(auto val : container) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

template<class Container1, class Container2>
bool container_equal(Container1& con1, Container2& con2) {
    auto first1 = std::begin(con1), last1 = std::end(con1);
    auto first2 = std::begin(con2), last2 = std::end(con2);
    for(; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if(*first1 != *first2) return false;
    }
    return (first1 == last1 && first2 == last2);
}

}
}
#endif