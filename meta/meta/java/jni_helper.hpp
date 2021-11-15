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

namespace meta {

namespace jni {

namespace helper {

struct j_void {};
struct j_boolean {
    j_boolean(const bool & v) : value(v) { }
    bool value;
};
struct j_byte {
    j_byte(const int8_t & v) : value(v) { }
    int8_t value;
};
struct j_char {
    j_char(const char & v) : value(v) { }
    char value;
};
struct j_short {
    j_short(const short & v) : value(v) { }
    short value;
};
struct j_int {
    j_int(const int & v) : value(v) { }
    int value;
};
struct j_long {
    j_long(const long & v) : value(v) { }
    long value;
};
struct j_float {
    j_float(const float & v) : value(v) { }
    float value;
};
struct j_double {
    j_double(const double & v) : value(v) { }
    double value;
};
struct j_string {
    j_string(const char * v) : value(v) { }
    j_string(const std::string & v) : value(v) { }
    std::string value;
};

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
    
    template<typename E>
    j_array(const std::vector<E> & vv) {
        for (const E & v : vv) {
            _values.push_back(value_type(v));
        }
    }
    std::vector<value_type> _values;
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
    
    static inline std::string sig(const j_object & jo = j_object::placeholder()) {
        if constexpr (is_array_t<T0>) {
            using T1 = typename T0::value_type;
            return
                std::string("[")
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
                 throw "Unsupported basic types, try j_type."
                 );
        } else {
            using T1 = T0;
            std::cout << typeid(T1).name() << std::endl;
            return
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
                throw "Unsupported basic types, try j_type";
        }
    }
};




template<typename R, typename... Args>
class j_function {
public:
    
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
                using T0 = std::remove_reference_t<std::remove_const_t<decltype(args)>>;

//                constexpr int index = meta::arg::index_of<T0, Args...>::index;
                
                std::cout << "T0: " << typeid(T0).name() << std::endl;
                std::cout << "Args: " << meta::arg::log_list<Args...>::type_names() << std::endl;
                
//                if constexpr (index >= 0) {
//                    _vvt.emplace_back(variant_type(std::in_place_index<index>, args));
//                    _vsig.emplace_back(T0::sig());
//                } else {
//                    _vvt.emplace_back(variant_type(args));
//                    _vsig.emplace_back(j_type<T0>::sig());
//                }
            }(), nullptr)...
        };
    }
    
    std::string sig() const {
        std::string _sig = "(";
        _sig += meta::string::join(_vsig);
        _sig += ")";
        _sig += j_type<R>::sig();
        return _sig;
    }
    
    std::string fullname() const {
        std::string _fn = j_type<R>::sig();
        _fn += " ";
        _fn += _name;
        _fn += "(";
        _fn += meta::string::join(_vsig, ",");
        _fn += ");";
        return _fn;
    }
    
private:
    std::string _name;
    std::vector<variant_type> _vvt;
    std::vector<std::string> _vsig;
};


}

}

}



#endif /* jni_helper_hpp */
