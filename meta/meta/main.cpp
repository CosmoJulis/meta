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


template<meta::class_utility::literal_string lit>
void Print() {
    // The size of the string is available as a constant expression.
    constexpr auto size = sizeof(lit.value);
    // and so is the string's content.
    constexpr auto contents = lit.value;
    
    
    std::cout << "Size: " << size << ", Contents: " << contents << std::endl;
}

int main(int argc, const char * argv[]) {
    Print<"literal string">(); // Prints "Size: 15, Contents: literal string"


    
    constexpr char a[15] = "literal string";
    
    Print<a>();
    
    return 0;
//    auto jc = j_call<j_void, j_boolean, j_string>(j_object(), "method", true, "hello world");
//    std::cout << j_object().classname() << std::endl;
    
    auto jc = j_call<j_void,
    j_boolean,
    j_byte,
    j_char,
    j_short,
    j_int,
    j_long,
    j_float,
    j_double,
    j_string
    >
    (j_object(), "method",
     true,
     0x1,
     'c',
     2,
     4,
     8,
     0.1,
     0.2,
     "hello world"
     );

    auto jm = j_method<j_void, j_boolean>("class", "m", true);


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
//     0x1,
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
