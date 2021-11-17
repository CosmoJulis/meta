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

#pragma mark - jni type

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

struct j_object : j_type {
    static std::string classname();
    
    static inline std::string sig() {
        return std::string("L") + meta::string::join(meta::string::split(classname(), "."), "/") + ";";
    }
};

struct j_string : j_object {
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



template<typename R, typename ... Args>
struct j_interface_object : j_object {
    // TODO interface base
};



template <typename T>
struct j_array {
    static inline std::string sig() {
        return std::string("[") + T::sig();
    }
    
    using value_type = T;
    
    template <typename E>
    j_array(const std::vector<E> & vv) { // TODO: vector to iterable
        for (const E & v : vv) {
            values.push_back(value_type(v));
        }
    }
    std::vector<value_type> values;
};


template <typename T>
struct is_j_array {
    static inline constexpr bool value = false;
};

template <typename T>
struct is_j_array<j_array<T>> {
    static inline constexpr bool value = true;
};

template <typename T>
inline constexpr bool is_j_array_t = is_j_array<T>::value;


#pragma mark - jni function/static function

template <typename R, typename ... Args>
class j_function {
private:
    class j_arg_placeholder {
    private:
        j_arg_placeholder() { }
    };
    
public:
    
    static_assert(
        meta::arg::is::all_base_of_v<j_type, R, Args...> &&
        !meta::arg::is::any_const_v<R, Args...> &&
        !meta::arg::is::any_reference_v<R, Args...> &&
        !meta::arg::is::any_pointer_v<R, Args...>,
        "Unsupported basic types, try j_type");


    using variant_type = std::conditional_t<
                                sizeof...(Args) == 0,
                                std::variant<j_arg_placeholder>,
                                std::variant<Args...>>;
    
    j_function(const std::string & name, const Args & ... args) : _name(name) {
        (void)std::initializer_list<nullptr_t>{
            ([&args, this] {
                using T0 = std::remove_cvref_t<decltype(args)>;
                constexpr int index = meta::arg::index_of<T0, Args...>::index;
                if constexpr (index >= 0) {
                    _vvt.emplace_back(variant_type(std::in_place_index<index>, args));
                } else {
                    _vvt.emplace_back(variant_type(args));
                }
            }(), nullptr)...
        };
    }
    
    j_function(const char * name, const Args & ... args) : j_function(name, args...) { }
    
    std::string sig() const {
        std::string _sig = "(";
        _sig += meta::string::join(_sigs());
        _sig += ")";
        _sig += R::sig();
        return _sig;
    }
    
    virtual std::string fullname() const {
        std::string _fn = R::sig();
        _fn += " ";
        _fn += _name;
        _fn += "(";
        _fn += meta::string::join(_sigs(), ", ");
        _fn += ");";
        return _fn;
    }
    
private:
    
    std::string _name;
    std::vector<variant_type> _vvt;
    
protected:
    std::vector<std::string> _sigs() const {
        std::vector<std::string> vs;
        for (const auto & vt : _vvt) {
            std::visit([&vs](const auto & k){
                if constexpr (!std::is_same_v<std::remove_cvref_t<decltype(k)>, j_arg_placeholder>) {
                    vs.push_back(std::decay_t<decltype(k)>::sig());
                }
            }, vt);
        }
        return vs;
    }

};


template <typename R, typename ... Args>
class j_static_function : public j_function<R, Args...> {
public:
    j_static_function(const std::string & name, const Args & ... args) : j_function<R, Args...>(name, args...) { }
    
    std::string fullname() const override {
        std::string _fn = j_function<R, Args...>::fullname();
        return "static " + _fn;
    }
};


#pragma mark - jni cached class

struct j_class {
    j_class(const std::string & name) : classname(name) { }
    std::string classname;
};


#pragma mark - jni call


template <typename R, typename ... Args>
class j_call {
public:
    j_call(const j_class & c, const j_static_function<R, Args...> & sf) {
        std::cout << "class<" << c.classname << "> call \"" << sf.fullname() << "\"" << std::endl;
    }

    j_call(const std::string & classname, const std::string & function, const Args & ... args) :
    j_call(j_class(classname), j_static_function<R, Args...>(function, args...)) { }

    
    j_call(const char * classname, const char * function, const Args & ... args) :
    j_call(std::string(classname), std::string(function), args...) { }
    

    j_call(const j_object & o, const j_function<R, Args...> & f) {
        std::cout << "object<" << o.classname() << "> call: \"" << f.fullname() << "\"" << std::endl;
    }
    
    j_call(const j_object & o, const std::string & function, const Args & ... args) :
    j_call(o, j_function<R, Args...>(function, args...)) { }
    
    j_call(const j_object & o, const char * function, const Args & ... args) :
    j_call(o, std::string(function), args...) { }
    
    virtual void execute() {
        
    }
    
private:

};





template <typename R, typename ... Args>
class my_j_call : public j_call<R, Args...> {
public:
    using j_call<R, Args...>::j_call;

    void execute() override {
        
    }
};

/*
 *  jobject call function
 *  jclass call static function
 *
 void _vibrate(float duration)
 {
     JNIEnv * env = get_JNI_Env();
     jclass jcls = get_bridge_java_class();
     jobject jobj = get_bridge_java_singleton();
     if (!env || !jcls || !jobj) return;

     static jmethodID jmethod = nullptr;
     if (!jmethod) {
         jmethodID tmp = env->GetMethodID(jcls, "vibrate", "(F)V");
         if (env->ExceptionCheck()) return;
         jmethod = tmp;
     }
     if (jmethod) {
         jfloat f = duration;
         env->CallVoidMethod(jobj, jmethod, duration);
     }
 }
 */


}

}

}



#endif /* jni_helper_hpp */
