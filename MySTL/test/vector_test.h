#ifndef _VECTOR_TEST_H_
#define _VECTOR_TEST_H_

#include "../vector.h"
#include "test_utils.h"

#include <vector>

#include <array>
#include <cassert>
#include<iostream>
#include <iterator>
#include <string>

namespace mystl {
namespace vector_test {
template<class T>
using stdVec = std::vector < T >;

template<class T>
using tsVec = mystl::vector < T >;

void testCase1();
void testCase2();
void testCase3();
void testCase4();
void testCase5();
void testCase6();
void testCase7();
void testCase8();
void testCase9();
// void testCase10();
void testCase11();
void testCase12();
void testCase13();
void testCase14();

void testAllCases();

}
}

#endif