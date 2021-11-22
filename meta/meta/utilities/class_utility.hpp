//
//  class_utility.hpp
//  meta
//
//  Created by Cosmo Julis on 11/22/21.
//

#ifndef class_utility_hpp
#define class_utility_hpp

#include <cxxabi.h>


namespace meta {

namespace class_utility {

    template <typename T>
    static inline const std::string classname() {
        int status;
        // TODO: portablity test
        std::string actual_class_name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
        if (status != 0) {
            throw "Class " + std::string(typeid(T).name()) + " parse error";
        } else {
            return actual_class_name;
        }
    }

}

}

#endif /* class_utility_hpp */
