//
//  class_utility.hpp
//  meta
//
//  Created by Cosmo Julis on 11/22/21.
//

#ifndef class_utility_hpp
#define class_utility_hpp

#include <cxxabi.h>
#include <version>


namespace meta::class_utility {

    template <typename T>
    static inline const std::string classname() {
        int status;
        /* TODO: portablity test
         * tested compiler:
         *              gcc
         *              llvm-gcc
         *              clang
         */
        std::string actual_class_name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
        if (status != 0) {
            throw "Class " + std::string(typeid(T).name()) + " parse error";
        } else {
            return actual_class_name;
        }
    }

#if _LIBCPP_STD_VER >= 20
    template<size_t N>
    struct string_literal {
        constexpr string_literal(const char (&str)[N]) {
            std::copy_n(str, N, value);
        }
        char value[N];
    };

    template<string_literal str>
    constexpr const char * string_literal_v = str.value;
#endif


}

#endif /* class_utility_hpp */



