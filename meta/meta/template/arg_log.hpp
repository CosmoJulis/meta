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


template <typename ... Args>
struct list {
    
    template <typename _T, typename ... _Args>
    struct _impl {
        static inline std::string _type_name() {
            return _impl<_T>::_type_name() + ", " + _impl<_Args...>::_type_name();
        }
    };

    template <typename _T>
    struct _impl<_T> {
        static inline std::string _type_name() {
            if constexpr (std::is_const_v<_T> && std::is_reference_v<_T>) {
                return std::string() + "const " + typeid(_T).name() + " &";
            }
            else if (std::is_const_v<_T>) {
                return std::string() + "const " + typeid(_T).name();
            }
            else if (std::is_reference_v<_T>) {
                return std::string() + typeid(_T).name() + " &";
            }
            else {
                return typeid(_T).name();
            }
        }
    };

    static inline std::string log = [](){
        return _impl<Args...>::_type_name();
    }();
};


}

}



#endif /* arg_log_hpp */
