//
//  main.cpp
//  test
//
//  Created by Cosmo Julis on 11/10/21.
//

#include <iostream>
#include "template/arg.hpp"
#include "java/jni_helper.hpp"




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


using namespace meta::jni::helper;


class A {
public:
    static inline const std::string get() {
        return "A";
    }
    A() {
        std::cout << "use " << get() << std::endl;
    }
};

class B : public A {
public:
    static inline const std::string get() {
        return "B";
    }
    B() {
        std::cout << "use " << get() << std::endl;
    }
};

int main(int argc, const char * argv[]) {

    auto jsm = j_static_method<j_void, j_interface<j_void>>("com.cosmojulis.jnitestapp.MainActivity", "callback", j_interface<j_void>("com.cosmojulis.meta.JniHelperInterface"));
    std::cout << "sl2577 sig = " << decltype(jsm)::method_sig() << std::endl;
    std::cout << "sl2577 fullname = " << jsm.fullname() << std::endl;;
    return 0;
}
