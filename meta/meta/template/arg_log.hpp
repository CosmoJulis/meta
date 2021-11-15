//
//  arg_log.hpp
//  meta
//
//  Created by Cosmo Julis on 11/12/21.
//

#ifndef arg_log_hpp
#define arg_log_hpp

#include <string>

namespace meta {

namespace arg {


template<typename ... Args>
struct log_list {
    
    template<typename _T, typename ... _Args>
    struct _impl {
        static std::string type_name() {
            return std::string(typeid(_T).name()) + ", " + _impl<_Args...>::type_name();
        }
    };

    template<typename _T>
    struct _impl<_T> {
        static std::string type_name() {
            return typeid(_T).name();
        }
    };

    static std::string type_names() {
        return _impl<Args...>::type_name();
    }
};


}

}



#endif /* arg_log_hpp */
