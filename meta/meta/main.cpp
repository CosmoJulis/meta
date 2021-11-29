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


// dexmaker 注册 callback 签名函数
template <typename ... Args>
void callback(const std::function<void(Args...)> & callback) {
    
}




//class j_base_object {
//public:
//    static inline const std::string classname() {
//        return j_base_object().name();
//    }
//
//    virtual std::string name() const {
//        return "java.lang.Object";
//    }
//};
//
//template <meta::class_utility::string_literal T>
//class j_derive_object : public j_base_object {
//public:
//    static inline const std::string classname() {
//        return j_derive_object().name();
//    }
//
//    std::string name() const override {
//        return T.value;
//    }
//};
//
//
//
//void test(const j_base_object & m) {
//    std::cout << std::remove_cvref_t<decltype(m)>::classname() << std::endl;
//    std::cout << m.name() << std::endl;
//}

int main(int argc, const char * argv[]) {



    
    
//    auto jc = j_call<j_void,
//    j_boolean,
//    j_byte,
//    j_char,
//    j_short,
//    j_int,
//    j_long,
//    j_float,
//    j_double,
//    j_string
//    >
//    (j_base_object(), "method",
//     true,
//     0b1011'0101,
//     'c',
//     2,
//     4,
//     8'000'000,
//     0.1,
//     0.2,
//     "hello world"
//     );

    auto jm = j_static_method<j_void, j_boolean, j_object>("java.lang.String", "m", true, j_derive_object<"java.lang.Myclass">());
    std::cout << jm.fullname() << std::endl;


//    auto jsc = j_static_call<j_void,
//    j_boolean,
//    j_byte,
//    j_char,
//    j_short,
//    j_int,
//    j_long,
//    j_float,
//    j_double,
//    j_string
//    >
//    ("com.app.Activity", "method",
//     true,
//     0b10110101,
//     'c',
//     2,
//     4,
//     8,
//     0.1,
//     0.2,
//     "hello world"
//     );
//
//
    
    return 0;
}
