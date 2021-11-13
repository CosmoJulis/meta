//
//  jni_helper.hpp
//  meta
//
//  Created by Cosmo Julis on 11/12/21.
//

#ifndef jni_helper_hpp
#define jni_helper_hpp

#include "../utilities/string_utility.hpp"
#include "../template/arg_index.hpp"

namespace meta {

namespace jni {

namespace helper {

struct j_void {};
struct j_boolean {};
struct j_byte {};
struct j_char {};
struct j_short {};
struct j_int {};
struct j_long {};
struct j_float {};
struct j_double {};
struct j_string {};

class j_object {
public:
    static j_object & placeholder() {
        static j_object _placeholder = j_object();
        return _placeholder;
    }
    
    j_object(const std::string & classname) : _classname(classname) { }

    std::string sig() const {
        if (&(placeholder()) == this) {
            return "";
        }
        return std::string("L") + meta::string::join(meta::string::split(_classname, "."), "/") + ";";
    }
    
private:
    std::string _classname;
    j_object() { }
};

template<typename T>
struct j_array {
    using value_type = T;
};

template<typename T>
struct is_array {
    static inline constexpr bool value = false;
};

template<typename T>
struct is_array<j_array<T>> {
    static inline constexpr bool value = true;
};

template<typename T>
inline constexpr bool is_array_t = is_array<T>::value;


template<typename T>
struct j_type {
    using T0 = std::remove_reference_t<std::remove_const_t<T>>;
    using T1 = std::conditional_t<is_array_t<T0>, typename T0::value_type, T0>;
    
    static std::string sig(const j_object & jo = j_object::placeholder()) {
        return
            std::string(is_array_t<T0> ? "[" : "")
            +
            (
             std::is_same_v<T1, j_void> ? "V" :
             std::is_same_v<T1, j_boolean> ? "Z" :
             std::is_same_v<T1, j_byte> ? "B" :
             std::is_same_v<T1, j_char> ? "C" :
             std::is_same_v<T1, j_short> ? "S" :
             std::is_same_v<T1, j_int> ? "I" :
             std::is_same_v<T1, j_long> ? "L" :
             std::is_same_v<T1, j_float> ? "F" :
             std::is_same_v<T1, j_double> ? "D" :
             std::is_same_v<T1, j_string> ? "Ljava/lang/String;" :
             std::is_same_v<T1, j_object> ? jo.sig() :
             throw "Unsupported basic types."
             );
    }
};


class j_function_placeholder {
    j_function_placeholder() { }
};

template<typename R, typename... Args>
class j_function {
public:
    using variant_type = std::conditional_t<
                                sizeof...(Args) == 0,
                                std::variant<j_function_placeholder>,
                                std::variant<Args...>>;
    
    j_function(const std::string & name, const Args & ... args) : _name(name) {
        (void)std::initializer_list<nullptr_t>{
            ([&args, this] {
                constexpr int index = meta::arg::index_of<std::remove_const_t<std::remove_reference_t<decltype(args)>>, Args...>::index;
                if constexpr (index >= 0) {
                    _vvt.emplace_back(variant_type(std::in_place_index<index>, args));
                } else {
                    _vvt.emplace_back(args);
                }
            }(), nullptr)...
        };
    }
    
private:
    std::string _name;
    std::vector<variant_type> _vvt;
};


}

}

}



#endif /* jni_helper_hpp */
