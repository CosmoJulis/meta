//
//  main.cpp
//  test
//
//  Created by Cosmo Julis on 11/10/21.
//

#include <iostream>
#include <vector>
#include <variant>
#include <list>

//#include "utilities/string_utility.hpp"
//#include "template/arg_index.hpp"
//#include "template/arg_list_log.hpp"


//class JavaCppBridgeBlockPlaceholder {
//private:
//    JavaCppBridgeBlockPlaceholder() { }
//};
//
//class JavaCppBridgeClassWrapper {
//public:
//    JavaCppBridgeClassWrapper(const std::string & classname) : _classname(classname) { }
//    std::string getSig() const {
//        if (&(placeholder()) == this) {
//            return "";
//        }
//        return std::string("L") + meta::string::join(meta::string::split(_classname, "."), "/") + ";";
//    }
//    static JavaCppBridgeClassWrapper & placeholder() {
//        static JavaCppBridgeClassWrapper singleton = JavaCppBridgeClassWrapper();
//        return singleton;
//    }
//private:
//    JavaCppBridgeClassWrapper() { }
//    std::string _classname;
//};
//
//
//template<typename T, bool isArray = false>
//struct JavaCppBridgeType {
//
//    using T0 = std::remove_reference_t<std::remove_const_t<T>>;
//
//    static std::string getSig(const JavaCppBridgeClassWrapper & w = JavaCppBridgeClassWrapper::placeholder()) {
//        return
//            std::string()
//            +
//            (isArray ? "[" : "")
//            +
//            (std::is_same_v<T0, void> ? "V" :
//            std::is_same_v<T0, bool> ? "Z" :
//            std::is_same_v<T0, uint8_t> ? "B" :
//            std::is_same_v<T0, char> ? "C" :
//            std::is_same_v<T0, short> ? "S" :
//            std::is_same_v<T0, int> ? "I" :
//            std::is_same_v<T0, long> ? "L" :
//            std::is_same_v<T0, float> ? "F" :
//            std::is_same_v<T0, double> ? "D" :
//            (std::is_same_v<T0, std::string> || std::is_same_v<T0, char *>) ? "Ljava/lang/String;" :
//            std::is_same_v<T0, JavaCppBridgeClassWrapper> ? w.getSig() :
//            throw "Unsupported basic types.");
//    }
//};
//
//template<typename T, typename ... Args>
//struct JavaCppBridgeTypeList {
//
//};
//
//
//
//template<typename R, typename... Args>
//class JavaCppBridgeBlock {
//public:
//
//    using VariantType = std::conditional_t<sizeof...(Args) == 0, std::variant<JavaCppBridgeBlockPlaceholder>, std::variant<Args...>>;
//
//
//    JavaCppBridgeBlock(const std::string & function, const Args & ... args) : _function(function) {
//        (void)std::initializer_list<nullptr_t>{
//            ([&args, this] {
//                constexpr int index = meta::arg::index_of<std::remove_const_t<std::remove_reference_t<decltype(args)>>, Args...>::index;
//                if constexpr (index >= 0) {
//                    _vcv.emplace_back(VariantType(std::in_place_index<index>, args));
//                } else {
//                    _vcv.emplace_back(args);
//                }
//            }(), nullptr)...
//        };
//    }
//
//
//    std::string getSignature() const {
//
//        return "(" + + ")" + JavaCppBridgeType<R>::getSig();
//    }
//
//
//private:
//    std::string _function;
//    std::vector<VariantType> _vcv;
//};


//int main(int argc, const char * argv[]) {

//    auto j = JavaCppBridgeBlock<void>("");
//    auto jj = JavaCppBridgeBlock<void, double, int, double>({"", 0.1, 0.1, 0.1});
    
//    auto jjj = JavaCppBridgeBlock<void, double, int, float, long, JavaCppBridgeClassWrapper, std::string>("", 0.1, 1, 0.2, 2, JavaCppBridgeClassWrapper("hellworld"), "hello");
//
//    std::cout << JavaCppBridgeType<void>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<bool>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<uint8_t>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<char>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<short>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<int>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<long>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<float>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<double>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<char *>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<std::string>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<JavaCppBridgeClassWrapper>::getSig() << std::endl;
//    std::cout << JavaCppBridgeType<JavaCppBridgeClassWrapper>::getSig(JavaCppBridgeClassWrapper("com.application.Activity")) << std::endl;

    
//    return 0;
//}


using namespace std;

template<typename T>
struct has_data_size
{
  template<typename Y>
    static constexpr bool checkMethods(decltype(std::declval<T>().data()) returnTypeOfData = nullptr,
                                       decltype(std::declval<T>().size()) returnTypeOfSize = 0)
    {
      if constexpr (std::is_convertible_v<decltype(returnTypeOfData), const char*> &&
                    std::is_convertible_v<decltype(returnTypeOfSize), int>) {
        return true;
      } else {
        return false;
      }
    }

  template<typename Y>
    static constexpr bool checkMethods(...)
    {
      return false;
    }

  static constexpr bool value = checkMethods<T>(nullptr, 0);
};


struct Foo {};

class Bar {
public:
  char* data() {
    return nullptr;
  }
    int size() {
        return 0;
    }
private:
    Bar(int a) { }
};



#include "java/jni_helper.hpp"


int main(int argc, const char * argv[]) {
    using namespace meta::jni::helper;
    
    

    
//    return 0;
    
    auto fv = j_function<j_void>("foo");
//    std::cout << fv.fullname() << std::endl;
    
    auto fi = j_function<j_int, j_int>("bar", 1);
//    std::cout << fi.fullname() << std::endl;
    
    auto fii = j_function<j_char, j_int, j_int>("bar", 1, 2);
//    std::cout << fii.fullname() << std::endl;
    

//    auto fs = j_function<j_void, j_string>("foo", "hello ");
//    std::cout << fs.fullname() << std::endl;


//    std::vector<int> vi;
//    vi.push_back(1);
//    vi.push_back(2);
//
//    std::vector<double> vd;
//    vd.push_back(0.1);
//    vd.push_back(0.2);
//
//    std::vector<std::string> vs;
//    vs.push_back("hello");
//    vs.push_back("world");
//
//
//    auto ffs = j_function<
//        j_void,
//        j_array<j_int>,
//        j_array<j_double>,
//        j_array<j_string>>
//        ("foo",
//         vi,
//         vd,
//         vs);

    
    
    return 0;
}
