//
//  jni_helper.hpp
//  meta
//
//  Created by Cosmo Julis on 11/12/21.
//

#ifndef jni_helper_hpp
#define jni_helper_hpp

#include <variant>
#include <unordered_map>
#include "jni.h"
#include "../utilities/string_utility.hpp"
#include "arg.hpp"


namespace meta {

namespace jni {

namespace helper {


#pragma mark - jni jclass jmethodid cached
static std::unordered_map<std::string, jclass> jclass_pointer_map;
static std::unordered_map<std::string, jmethodID> jmethod_id_pointer_map;


#pragma mark - jni env

class j_env {
public:
    j_env(JNIEnv * env = nullptr) : _env(env) { }
    
    JNIEnv * pointer() const {
        return _env;
    }

private:
    JNIEnv * _env;
};


class j_vm {
public:
    static j_vm & shared() {
        static j_vm jvm = j_vm();
        return jvm;
    }
    
    void load_vm(JavaVM * vm) {
        j_vm::shared()._vm = vm;
    }
    
    void clear_vm() {
        jclass_pointer_map.clear();
        jmethod_id_pointer_map.clear();
    }
    
    
    j_env env() {
        if (_j_env.pointer() != nullptr) {
            return _j_env;
        } else {
            JNIEnv * env;
            jint ret = _vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
            if (ret == JNI_EDETACHED) {
//                if (_vm->AttachCurrentThread(&env, nullptr) >= 0) {
                if (_vm->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr) >= 0) {
                    _j_env = j_env(env);
                }
            }
        }
        return _j_env;
    }
    
private:
    j_env _j_env;
    j_vm() { }
    JavaVM * _vm;
};




#pragma mark - jni class

class j_class {
public:
    
    j_class(const std::string & name = "") : _classname(name) {

    }
    
    std::string classname() const {
        return _classname;
    }
    
    std::string sig() const {
        return meta::string::join(meta::string::split(_classname, "."), "/");
    }
    
    jclass pointer(const j_env & env) const {
//        if (jclass_pointer_map.find(_classname) != jclass_pointer_map.end()) {
        if (jclass_pointer_map.contains(_classname)) {
            return jclass_pointer_map[_classname];
        } else {
            jclass jcls = env.pointer()->FindClass(sig().c_str());
            if (env.pointer()->ExceptionCheck()) {
                return nullptr;
            }
            jclass_pointer_map[_classname] = jcls;
            return jcls;
        }
    }
    
private:

    std::string _classname;

};

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

class j_object : j_type {
public:
    j_object(const jobject & jo = nullptr) : _jo(jo) { }
    
    static std::string classname() {
        return "java.lang.Object";
    }
    
    static inline std::string sig() {
        return std::string("L") + meta::string::join(meta::string::split(classname(), "."), "/") + ";";
    }
    
    static j_object & placeholder() {
        static j_object _placeholder = j_object();
        return _placeholder;
    }
    
    jobject pointer() const {
        return _jo;
    }
    
private:
    
    jobject _jo;

};

class j_string : public j_object {
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
class j_method {
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
    
    static_assert(!is_j_array_t<R>, "Return type can not be an array");

    j_method() { }

    using variant_type = std::conditional_t<
                                sizeof...(Args) == 0,
                                std::variant<j_arg_placeholder>,
                                std::variant<Args...>>;
    
    j_method(const std::string & classname, const std::string & method_name, const Args & ... args) : _jcls(classname), _method_name(method_name) {
        (void)std::initializer_list<nullptr_t>{
            ([&args, this] {
//                using T0 = std::remove_const_t<std::remove_reference_t<decltype(args)>>;
                using T0 = std::remove_cvref_t<decltype(args)>;
                constexpr int index = meta::arg::index_of<T0, Args...>::index;
                if constexpr (index >= 0) {
                    _vvt.emplace_back(variant_type(std::in_place_index<index>, args));
                } else {
                    _vvt.emplace_back(variant_type(args));
                }
            }(), nullptr)...
        };
        
        pass_args(args...);

    }
    
    virtual void pass_args(const Args & ... args) {
        _call = [this, &args...](const j_env & je, const j_object & jo){
            JNIEnv * env = nullptr;
            jobject jobj = jo.pointer();
            jmethodID jmethod = this->jmethod_id_pointer(je);
            
            R r;
            if constexpr (std::is_same_v<R, j_void>) {
                env->CallVoidMethod(jobj, jmethod, args...);
                if (env->ExceptionCheck()) throw "Call java method error";
                return j_void();
            }
            else if (std::is_same_v<R, j_boolean>) {
                jboolean jb = env->CallBooleanMethod(jobj, jmethod, args...);
                r = j_boolean(jb);
            }
            else if (std::is_same_v<R, j_byte>) {
                jbyte jb = env->CallByteMethod(jobj, jmethod, args...);
                r = j_byte(jb);
            }
            else if (std::is_same_v<R, j_char>) {
                jchar jc = env->CallCharMethod(jobj, jmethod, args...);
                r = j_char(jc);
            }
            else if (std::is_same_v<R, j_short>) {
                jshort js = env->CallShortMethod(jobj, jmethod, args...);
                r = j_short(js);
            }
            else if (std::is_same_v<R, j_int>) {
                jint ji = env->CallIntMethod(jobj, jmethod, args...);
                r = j_int(ji);
            }
            else if (std::is_same_v<R, j_long>) {
                jlong jl = env->CallLongMethod(jobj, jmethod, args...);
                r = j_long(jl);
            }
            else if (std::is_same_v<R, j_float>) {
                jfloat jf = env->CallFloatMethod(jobj, jmethod, args...);
                r = j_float(jf);
            }
            else if (std::is_same_v<R, j_double>) {
                jdouble jd = env->CallDoubleMethod(jobj, jmethod, args...);
                r = j_double(jd);
            }
            else if (std::is_same_v<R, j_string>) {
                jstring js = env->CallDoubleMethod(jobj, jmethod, args...);
//                r =
                // TODO: string cast
            }
            else if (std::is_base_of_v<j_object, R>) {
                jobject jo = env->CallObjectMethod(jobj, jmethod, args...);
                r = j_object(jo);
            }
            
            if (env->ExceptionCheck()) throw "Call java method error";
            
            return r;
        };
    }
    
    std::string sig() const {
        std::string _sig = "(";
        _sig += meta::string::join(_sigs());
        _sig += ")";
        _sig += R::sig();
        return _sig;
    }
    
    virtual std::string fullname() const {
        std::string _fn = "<" + _jcls.classname() + "> ";
        _fn += R::sig();
        _fn += " ";
        _fn += _method_name;
        _fn += "(";
        _fn += meta::string::join(_sigs(), ", ");
        _fn += ");";
        return _fn;
    }
    
    R call(const j_env & je, const j_object & jo) {
        return _call(je, jo);
    }
    
    jmethodID jmethod_id_pointer(const j_env & env) const {
        std::string fn = fullname();
//        if (jmethod_id_pointer_map.find(fn) != jmethod_id_pointer_map.end()) {
        if (jmethod_id_pointer_map.contains(fn)) {
            return jmethod_id_pointer_map[fn];
        } else {
            jclass jcls = _jcls.pointer(env);
            jmethodID jmethod_id = env.pointer()->GetMethodID(jcls, _method_name.c_str(), sig().c_str());
            if (env.pointer()->ExceptionCheck()) {
                return nullptr;
            }
            jmethod_id_pointer_map[fn] = jmethod_id;
            return jmethod_id;
        }
    }
    
    std::string method_name() const {
        return _method_name;
    }
    

    
private:

    std::vector<variant_type> _vvt;
    std::function<R(const j_env &, const j_object &)> _call;

protected:
    
    j_class _jcls;
    std::string _method_name;
    
    std::vector<std::string> _sigs() const {
        std::vector<std::string> vs;
        for (const auto & vt : _vvt) {
            std::visit([&vs](const auto & k){
//                if constexpr (!std::is_same_v<std::remove_const_t<std::remove_reference_t<decltype(k)>>, j_arg_placeholder>) {
                if constexpr (!std::is_same_v<std::remove_cvref_t<decltype(k)>, j_arg_placeholder>) {
                    vs.push_back(std::decay_t<decltype(k)>::sig());
                }
            }, vt);
        }
        return vs;
    }

};


template <typename R, typename ... Args>
class j_static_method : public j_method<R, Args...> {
public:
    using j_method<R, Args...>::j_method;
    
    void pass_args(const Args & ... args) override {
        _call = [this, &args...](const j_env & je){
            JNIEnv * env = je.pointer();
            jclass jcls = j_method<R, Args...>::_jcls.pointer(env);
            jmethodID jmethod = this->jmethod_id_pointer(je);
            
            R r;
            if constexpr (std::is_same_v<R, j_void>) {
                env->CallStaticVoidMethod(jcls, jmethod, args...);
                if (env->ExceptionCheck()) throw "Call java method error";
                return j_void();
            }
            else if (std::is_same_v<R, j_boolean>) {
                jboolean jb = env->CallStaticBooleanMethod(jcls, jmethod, args...);
                r = j_boolean(jb);
            }
            else if (std::is_same_v<R, j_byte>) {
                jbyte jb = env->CallStaticByteMethod(jcls, jmethod, args...);
                r = j_byte(jb);
            }
            else if (std::is_same_v<R, j_char>) {
                jchar jc = env->CallStaticCharMethod(jcls, jmethod, args...);
                r = j_char(jc);
            }
            else if (std::is_same_v<R, j_short>) {
                jshort js = env->CallStaticShortMethod(jcls, jmethod, args...);
                r = j_short(js);
            }
            else if (std::is_same_v<R, j_int>) {
                jint ji = env->CallStaticIntMethod(jcls, jmethod, args...);
                r = j_int(ji);
            }
            else if (std::is_same_v<R, j_long>) {
                jlong jl = env->CallStaticLongMethod(jcls, jmethod, args...);
                r = j_long(jl);
            }
            else if (std::is_same_v<R, j_float>) {
                jfloat jf = env->CallStaticFloatMethod(jcls, jmethod, args...);
                r = j_float(jf);
            }
            else if (std::is_same_v<R, j_double>) {
                jdouble jd = env->CallStaticDoubleMethod(jcls, jmethod, args...);
                r = j_double(jd);
            }
            else if (std::is_same_v<R, j_string>) {
                jstring js = env->CallStaticDoubleMethod(jcls, jmethod, args...);
//                r =
                // TODO: string cast
            }
            else if (std::is_base_of_v<j_object, R>) {
                jobject jo = env->CallStaticObjectMethod(jcls, jmethod, args...);
                r = j_object(jo);
            }
            
            if (env->ExceptionCheck()) throw "Call java method error";
            
            return r;
        };
    }
    
    R call(const j_env & je) {
        return _call(je);
    }
    
    std::string fullname() const override {
        std::string _fn = "<" + j_method<R, Args...>::_jcls.classname() + "> ";
        _fn += "static ";
        _fn += R::sig();
        _fn += " ";
        _fn += j_method<R, Args...>::_method_name;
        _fn += "(";
        _fn += meta::string::join(j_method<R, Args...>::_sigs(), ", ");
        _fn += ");";
        return _fn;
    }
    
private:

    std::function<R(const j_env &)> _call;

};





#pragma mark - jni call


template <typename R, typename ... Args>
class j_call {
public:
    j_call(const j_static_method<R, Args...> & sf) {
        _jsmethod = sf;
        std::cout << "call \"" << sf.fullname() << "\"" << std::endl;
    }

    j_call(const std::string & classname, const std::string & method_name, const Args & ... args) :
    j_call(j_static_method<R, Args...>(classname, method_name, args...)) { }
    
    
    j_call(const j_object & o, const j_method<R, Args...> & f) {
        _jobj = o;
        _jmethod = f;
        std::cout << "object<" << o.classname() << "> call: \"" << f.fullname() << "\"" << std::endl;
    }
    
    j_call(const j_object & o, const std::string & function, const Args & ... args) :
    j_call(o, j_method<R, Args...>(function, args...)) { }
    
    j_call(const j_object & o, const char * function, const Args & ... args) :
    j_call(o, std::string(function), args...) { }
    
    virtual void execute() {
        j_env env = j_vm::shared().env();
        if (&_jobj == &(j_object::placeholder())) {
            _jsmethod.call(env);
        } else {
            _jmethod.call(env, _jobj);
        }
    }
    
private:
    j_static_method<R, Args...> _jsmethod;
    j_method<R, Args...> _jmethod;
    j_object & _jobj = j_object::placeholder();

};





template <typename R, typename ... Args>
class my_j_call : public j_call<R, Args...> {
public:
    using j_call<R, Args...>::j_call;

    void execute() override {
        
    }
};





}

}

}


jint JNI_OnLoad(JavaVM * vm, void * reserved) {
    meta::jni::helper::j_vm::shared().load_vm(vm);
    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM * vm, void * reserved) {
    meta::jni::helper::j_vm::shared().clear_vm();
}


#endif /* jni_helper_hpp */
