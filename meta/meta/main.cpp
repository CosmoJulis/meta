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



int main(int argc, const char * argv[]) {
    using namespace meta::jni::helper;
    
//    auto jc = j_call<j_void, j_interface_object>{
//        "com.cosmojulis.jnitestapp.MainActivity",
//        "test_interface_object",
//        [](){
//
//        }
//    };
//    jc.execute();

//    auto jc = j_call<j_void, j_int>("com.application.Activity", "idid", 1);
//    jc.execute();
    
//    auto jc = j_call<j_string, j_string, j_string>(
//            "com.cosmojulis.jnitestapp.MainActivity",
//            "test_combine",
//            "hello",
//            "world"
//            );
//    std::string r = jc.execute();
    
    auto jc = j_call<j_void, j_string, j_string>("hsfsd", "sfsfd", "foo", "bar");
    jc.execute();
    
    return 0;
}
