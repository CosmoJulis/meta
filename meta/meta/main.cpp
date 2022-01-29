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



#include "console/console.hpp"



class Person : public meta::console::object {
public:
    int age;
    float height;
    int name;
    void set_age(int age) {
        std::cout << "set_age(" << age << ")" << std::endl;
    }
    void set_height(float height) {
        std::cout << "set_height(F" << height << ")" << std::endl;
    }
    void set_name(std::string name) {
        std::cout << "set_name(" << name << ")" << std::endl;
    }
};
    
    
//    void execute(const inst_code & code, const std::string & property) override {
//
//
//        using namespace meta::console;
//
//        switch (c) {
//            case i_age:
//                set_age(stack_manager::get_manager().pop_number());
//                break;
//            case i_height:
//                set_height(stack_manager::get_manager().pop_number());
//                break;
//            case i_name:
//                set_name(stack_manager::get_manager().pop_string());
//                break;
//            default:
//                throw "Nout found instruction " + std::to_string(c);
//        }
//    }
//};


void runloop();


int main(int argc, const char * argv[]) {
    
    using namespace meta::console;
    
    // set 0 name "hello world"
    Stack & mgr = Stack::get_manager();
    mgr.push(Code::SET);
    mgr.push(0);
    mgr.push("name");
    mgr.push("hello world");
    
    
    // show get 0 name
//    mgr.push(Code::SHOW);
//    mgr.push(Code::GET);
//    mgr.push(0);
//    mgr.push("name");

    
    runloop();
    
    return 0;
}


void runloop() {
    using namespace meta::console;
    Stack & mgr = Stack::get_manager();
    while (mgr.reg_stack.size() > 0) {
        std::stack<Reg> inst_stack;
        
        Reg r;
        do {
            r = mgr.pop();
            inst_stack.push(r);
        } while (r.type != INSTRUCTION);

        while (inst_stack.size() > 0) {
            Reg & r = inst_stack.top();
            std::cout << r << std::endl;
            inst_stack.pop();
        }
        
    }
}


