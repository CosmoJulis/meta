//
//  arg_list_log.h
//  meta
//
//  Created by Cosmo Julis on 11/12/21.
//

#ifndef arg_list_log_h
#define arg_list_log_h

#include <string>


template<typename T, typename ... Args>
struct arg_list_log_impl {
    static std::string type_name() {
        return std::string(typeid(T).name()) + ", " + arg_list_log_impl<Args...>::type_name();
    }
};

template<typename T>
struct arg_list_log_impl<T> {
    static std::string type_name() {
        return typeid(T).name();
    }
};

template<typename ... Args>
struct arg_list_log {
    static std::string get_type_names() {
        return arg_list_log_impl<Args...>::type_name();
    }
};

#endif /* arg_list_log_h */
