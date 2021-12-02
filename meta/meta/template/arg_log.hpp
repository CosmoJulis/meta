//
//  arg_log.hpp
//  meta
//
//  Created by Cosmo Julis on 11/12/21.
//

#ifndef arg_log_hpp
#define arg_log_hpp

#include <string>
#include "utility.hpp"

namespace meta::arg {


template <typename ... Args>
struct list {
    
    static_assert(sizeof...(Args) > 0, "Args is empty.");
    
    template <typename _T, typename ... _Args>
    struct _impl {
        static inline std::string _type_name() {
            return _impl<_T>::_type_name() + ", " + _impl<_Args...>::_type_name();
        }
    };

    template <typename _T>
    struct _impl<_T> {
        
        static inline const std::string _actual_type_name() {
            return meta::class_utility::classname<_T>();
        }
        
        static inline const std::string _type_name() {
            if constexpr (std::is_const_v<_T>) {
                return std::string() + "const " + _actual_type_name();
            }
            else if constexpr (std::is_reference_v<_T>) {
                if constexpr (std::is_const_v<std::remove_reference_t<_T>>) {
                    return std::string() + "const " + _actual_type_name() + " &";
                } else {
                    return std::string() + _actual_type_name() + " &";
                }
            }
            else {
                return _actual_type_name();
            }
        }
    };

    static inline const std::string log() {
        return _impl<Args...>::_type_name();
    };
};

template <typename ... Args>
static inline const std::string list_log = list<Args...>::log();



}



#endif /* arg_log_hpp */
