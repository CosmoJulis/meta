//
//  main.cpp
//  test
//
//  Created by Cosmo Julis on 11/10/21.
//

#include <iostream>
#include "template/arg.hpp"
#include "java/jni_helper.hpp"
#include "console/console.hpp"
#include "utilities/utility.hpp"
#include <version>
#include <vector>
#include <any>


using namespace meta::jni::helper;
using namespace meta::console;


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




#include "MyObject.hpp"


int main(int argc, const char * argv[]) {
        
    MyObject obj0 = MyObject(0);
    MyObject obj1 = MyObject(1);
    
    MyObject & o0 = dynamic_cast<MyObject &>(Pool::shared().find(0));
    MyObject & o1 = dynamic_cast<MyObject &>(Pool::shared().find(1));
    
    Manager & mgr = Manager::shared();



//    mgr.push(Code::SHOW);
//    mgr.push(Code::GREATER);
//    mgr.push(1);
//    mgr.push(0);

    
    mgr.push(Code::REPEAT);
    mgr.push(10);
    mgr.push(Code::SET);
    mgr.push(0);
    mgr.push("age");
    mgr.push(Code::ADD);
    mgr.push(Code::GET);
    mgr.push(0);
    mgr.push("age");
    mgr.push(1);
    
    
    mgr.push(Code::SHOW);
    mgr.push(Code::GET);
    mgr.push(0);
    mgr.push("age");
    
    mgr.execute();

    mgr.debug_log();

    return 0;
}




