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

class A { };
class B : A { };
class C : A { };




int main(int argc, const char * argv[]) {
    int a;
    jobject jhi;
    LOGV("sl2577 i = %d", a);
    auto jc = j_call<j_void, j_array<j_int, j_double, j_string>>(j_object(jhi), "callback", make_array(1, 2.0, "hello"));
    jc.execute();
    
    return 0;
}
