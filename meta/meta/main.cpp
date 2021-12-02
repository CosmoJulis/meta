//
//  main.cpp
//  test
//
//  Created by Cosmo Julis on 11/10/21.
//

#include <iostream>
#include "template/arg.hpp"
#include "java/jni_helper.hpp"
#include "utilities/utility.hpp"
#include <version>
#include <vector>
#include <any>


using namespace meta::jni::helper;


//using namespace std;
//
//template <typename T>
//struct has_data_size
//{
//  template <typename Y>
//    static constexpr bool checkMethods(decltype(std::declval<T>().data()) returnTypeOfData = nullptr,
//                                       decltype(std::declval<T>().size()) returnTypeOfSize = 0)
//    {
//      if constexpr (std::is_convertible_v<decltype(returnTypeOfData), const char*> &&
//                    std::is_convertible_v<decltype(returnTypeOfSize), int>) {
//        return true;
//      } else {
//        return false;
//      }
//    }
//
//  template <typename Y>
//    static constexpr bool checkMethods(...)
//    {
//      return false;
//    }
//
//  static constexpr bool value = checkMethods<T>(nullptr, 0);
//};
//
//
//struct Foo {};
//
//class Bar {
//public:
//  char* data() {
//    return nullptr;
//  }
//    int size() {
//        return 0;
//    }
//private:
//    Bar(int a) { }
//};


class A {
public:
    A() {
        std::cout << "A Construct\n";
    }
    
    A(const A & t) {
        std::cout << "A Copy\n";
    }
    
    A(A && t) {
        std::cout << "A Move\n";
    }
};

class B {
public:
    B() {
        std::cout << "B Construct\n";
    }
    
    B(const B & t) {
        std::cout << "B Copy\n";
    }
    
    B(B && t) {
        std::cout << "B Move\n";
    }
};

class C {
public:
    C() {
        std::cout << "C Construct\n";
    }
    
    C(const C & t) {
        std::cout << "C Copy\n";
    }
    
    C(C && t) {
        std::cout << "C Move\n";
    }
};

template <int index, typename ... Args>
void test(Args && ... args) {
    const auto & a = meta::arg::of<index, Args...>::get_value(std::forward<Args>(args)...);
    std::cout << "return 0\n";
}

int main(int argc, const char * argv[]) {
    auto b = B();
    test<0>(A(), b, C());

    
    
    return 0;
}
