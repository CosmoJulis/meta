//
//  jni_helper.hpp
//  meta
//
//  Created by Cosmo Julis on 11/12/21.
//

#ifndef jni_helper_hpp
#define jni_helper_hpp

#include "../utilities/string_utility.hpp"
#include "../template/arg.hpp"
#include <variant>

namespace meta {

namespace jni {

namespace helper {

struct j_type {
    static inline std::string sig();
};

struct j_void : j_type {
    static inline std::string sig() {
        return "V";
    }
};

struct j_boolean : j_type {
    static inline std::string sig() {
        return "Z";
    }
    
    j_boolean(const bool & v) : value(v) { }
    bool value;
};

struct j_byte : j_type {
    static inline std::string sig() {
        return "B";
    }

    j_byte(const int8_t & v) : value(v) { }
    int8_t value;
};

struct j_char : j_type {
    static inline std::string sig() {
        return "C";
    }

    j_char(const char & v) : value(v) { }
    char value;
};

struct j_short : j_type {
    static inline std::string sig() {
        return "S";
    }

    j_short(const short & v) : value(v) { }
    short value;
};

struct j_int : j_type {
    static inline std::string sig() {
        return "I";
    }

    j_int(const int & v) : value(v) { }
    int value;
};

struct j_long : j_type {
    static inline std::string sig() {
        return "L";
    }

    j_long(const long & v) : value(v) { }
    long value;
};

struct j_float : j_type {
    static inline std::string sig() {
        return "F";
    }

    j_float(const float & v) : value(v) { }
    float value;
};

struct j_double : j_type {
    static inline std::string sig() {
        return "D";
    }

    j_double(const double & v) : value(v) { }
    double value;
};

struct j_string : j_type {
    static inline std::string classname() {
        return "java.lang.String";
    }
    
    static inline std::string sig() {
        return std::string("L") + meta::string::join(meta::string::split(classname(), "."), "/") + ";";
    }

    j_string(const char * v) : value(v) { }
    j_string(const std::string & v) : value(v) { }
    std::string value;
};

struct j_object : j_type {
    static std::string classname();
    
    static inline std::string sig() {
        return std::string("L") + meta::string::join(meta::string::split(classname(), "."), "/") + ";";
    }
};

template<typename T>
struct j_array {
    static inline std::string sig() {
        return std::string("[") + T::sig();
    }
    
    using value_type = T;
    
    template<typename E>
    j_array(const std::vector<E> & vv) {
        for (const E & v : vv) {
            values.push_back(value_type(v));
        }
    }
    std::vector<value_type> values;
};


template<typename T>
struct is_j_array {
    static inline constexpr bool value = false;
};

template<typename T>
struct is_j_array<j_array<T>> {
    static inline constexpr bool value = true;
};

template<typename T>
inline constexpr bool is_j_array_t = is_j_array<T>::value;

// TODO: vector to iterable


template<typename R, typename... Args>
class j_function {
public:
    
    static_assert(std::is_base_of_v<j_type, R>, "Unsupported basic types, try j_type");
    // todo: add assert for args
    
    class j_arg_placeholder {
        j_arg_placeholder() { }
    };

    using variant_type = std::conditional_t<
                                sizeof...(Args) == 0,
                                std::variant<j_arg_placeholder>,
                                std::variant<Args...>>;
    
    j_function(const std::string & name, const Args & ... args) : _name(name) {
        (void)std::initializer_list<nullptr_t>{
            ([&args, this] {
                using T0 = std::remove_const_t<std::remove_reference_t<decltype(args)>>;
                constexpr int index = meta::arg::index_of<T0, Args...>::index;
                if constexpr (index >= 0) {
                    _vvt.emplace_back(variant_type(std::in_place_index<index>, args));
                } else {
                    _vvt.emplace_back(variant_type(args));
                }
            }(), nullptr)...
        };
    }
    
    std::string sig() const {
        std::string _sig = "(";
        _sig += meta::string::join(_sigs());
        _sig += ")";
        _sig += R::sig();
        return _sig;
    }
    
    std::string fullname() const {
        std::string _fn = R::sig();
        _fn += " ";
        _fn += _name;
        _fn += "(";
        _fn += meta::string::join(_sigs(), ",");
        _fn += ");";
        return _fn;
    }
    
private:
    
    std::string _name;
    std::vector<variant_type> _vvt;
    
    std::vector<std::string> _sigs() const {
        std::vector<std::string> vs;
        for (const auto & vt : _vvt) {
            std::visit([&vs](const auto & k){
                vs.push_back(std::decay_t<decltype(k)>::sig());
            }, vt);
        }
        return vs;
    }

};


}

}

}



#endif /* jni_helper_hpp */
