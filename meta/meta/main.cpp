//
//  main.cpp
//  test
//
//  Created by Cosmo Julis on 11/10/21.
//

#include <iostream>
#include "template/arg.hpp"
#include "java/jni_helper.hpp"
#include "utilities/class_utility.hpp"


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

namespace n {
class test_class_name { };
}
using namespace meta::jni::helper;

int main(int argc, const char * argv[]) {

    std::cout << meta::class_utility::classname<n::test_class_name>() << std::endl;
    // exception classes not in <stdexcept>, thrown by the implementation
    // instead of the user
//    std::bad_exception  e;
//    realname = abi::__cxa_demangle(e.what(), 0, 0, &status);
//    std::cout << e.what() << "\t=> " << realname << "\t: " << status << '\n';
//    free(realname);




//    auto jsm = j_static_method<j_void, j_interface<j_void>>("com.cosmojulis.jnitestapp.MainActivity", "callback", j_interface<j_void>("com.cosmojulis.meta.JniHelperInterface"));
//    std::cout << "sl2577 sig = " << decltype(jsm)::method_sig() << std::endl;
//    std::cout << "sl2577 fullname = " << jsm.fullname() << std::endl;;
    

    
    

    return 0;
}
