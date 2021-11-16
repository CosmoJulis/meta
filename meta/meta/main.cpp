//
//  main.cpp
//  test
//
//  Created by Cosmo Julis on 11/10/21.
//

#include <iostream>
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





int main(int argc, const char * argv[]) {

    using namespace meta::jni::helper;
    
    auto j = j_static_function<j_void, j_int, j_double, j_int, j_double>("idid", 1, 0.1, 2, 0.2);
    std::cout << j.fullname() << std::endl;
        

//    auto jc = j_call<j_void, j_int>(j_class("com.application.Activity"), j_static_function<j_void, j_int>("idid", 1));
    j_call<j_void, j_int>("com.application.Activity", "idid", 1);
    
    return 0;
}
