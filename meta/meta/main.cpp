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



#include "java/jni_helper.hpp"


int main(int argc, const char * argv[]) {
    using namespace meta::jni::helper;
//    auto f = j_function<j_void, j_int, j_double, j_string, j_object>("foo", 1, 1.5, "hello", j_object("com.application.Activity"));
    
    return 0;
}
