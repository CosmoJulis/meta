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

std::unordered_map<int, MyObject> id_object_map;

int main(int argc, const char * argv[]) {
    
    auto a = MyObject(0);
    id_object_map[0] = a;

    Manager & mgr = Manager::shared();

    // set 0 get 0 name "hello world"
    mgr.push(Code::SET);
    mgr.push(0);
    mgr.push(Code::GET);
    mgr.push(0);
    mgr.push("name");
    mgr.push("hello world");
    
    // show get 0 name
//    Statement second;
//    second.push(Code::SHOW);
//    second.push(Code::GET);
//    second.push(0);
//    second.push("name");
//    mgr.push(second);
    
    // repeat 10 show get 0 name
//    Stack third;
//    third.push(Code::REPEAT);
//    third.push(10);
//    third.push(Code::SHOW);
//    third.push(Code::GET);
//    third.push(0);
//    third.push("name");
//    mgr.push(third);
    
    mgr.execute();
    
    

    
    return 0;
}




