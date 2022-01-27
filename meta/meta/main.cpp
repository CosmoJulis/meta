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


#include "vm/vm.hpp"


class function_binding {
public:
    std::unordered_map<std::string, std::any> binding_map;
    
    virtual void binding() = 0;
    
    void execute(const std::string & cmd_string, const std::string & name) {
        if (binding_map.contains(cmd_string)) {
            auto cmd = binding_map[cmd_string];

        }
    }
};

class F : public function_binding {
public:
    
    
    
    void binding() override {
        auto aaa = &F::set_name;
        binding_map["set name"] = std::make_any<decltype(aaa)>(aaa);
    };
    
    void set_name(const std::string & name) {
        std::cout << "set name " << name << std::endl;
    }
};



class Person {
public:
    int age;
    int height;
    int name;
    void set_age(int age) {
        std::cout << "set_age(" << age << ")" << std::endl;
    }
    void set_height(int height) {
        std::cout << "set_height(" << height << ")" << std::endl;
    }
    void set_name(std::string name) {
        std::cout << "set_name(" << name << ")" << std::endl;
    }
    
    static std::unordered_map<std::string, std::any> mapper() {
        static std::unordered_map<std::string, std::any> umsa;
        if (umsa.size() == 0) {
            umsa["set_age"] = &Person::set_age;
            umsa["set_name"] = &Person::set_name;
        }
        return umsa;
    }
};



#if _LIBCPP_STD_VER >= 20
template <meta::class_utility::string_literal T>
#else
template <typename T>
#endif
class get {
    static inline const std::string name() {
#if _LIBCPP_STD_VER >= 20
        return T.value;
#else
        std::string actual_class_name = meta::class_utility::classname<T>();
        
        std::string define_class_name = *(meta::string::split(actual_class_name, "::").rbegin());
        
        return define_class_name;
#endif
    }
};

template <meta::class_utility::string_literal T, typename E>
class dynamic_func {
public:
    E func_ptr;
    dynamic_func(E e) : func_ptr(e) { }
    
    void action(const std::function<E> & func) {
        
    }
};


int main(int argc, const char * argv[]) {



    auto set_age = &Person::set_age;
    auto set_height = &Person::set_height;
    std::cout << meta::arg::list_log<decltype(set_age)> << std::endl;
    std::cout << meta::arg::list_log<decltype(set_height)> << std::endl;

    dynamic_func<"set_age", decltype(set_age)> st(set_age);
    Person p;


    
    
    return 0;
}
