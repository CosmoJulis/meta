//
//  jni_helper.hpp
//  meta
//
//  Created by Cosmo Julis on 11/12/21.
//

#ifndef jni_helper_hpp
#define jni_helper_hpp

#define Xcode
//#define AndroidStudio

#define DEBUG_ENABLED 1

#include <variant>
#include <any>
#include <unordered_map>
#include "utility.hpp"
#include "arg.hpp"


#ifdef Xcode
#include "jni.h"
#define LOGV(...)
#else
#include <jni.h>
#include <iostream>
#include "alog.h"
#endif



namespace meta {

    namespace jni {

        namespace helper {


#pragma mark - jni jclass jmethodid cached

            static std::unordered_map<std::string, jclass> jclass_pointer_map;
            static std::unordered_map<std::string, jmethodID> jmethod_id_pointer_map;
        
//            class j_class_native_methods;
//            static std::unordered_map<std::string, j_class_native_methods> jclass_name_native_methods_map;
        


        
#pragma mark - jni type

            struct j_type {
                static inline const std::string sig();
            };

            struct j_void : j_type {
                static inline const std::string sig() { return "V";}
                static inline j_void & placeholder() {
                    static j_void _placeholder = j_void();
                    return _placeholder;
                }
            };

            struct j_boolean : j_type {
                static inline const std::string sig() { return "Z";}

                j_boolean(const bool & v = false) : value(v) { }
                j_boolean(const jboolean & jb) : value(jb) { }

                bool value;

                operator bool() const {
                    return value;
                }

                operator jvalue() const {
                    return jvalue{.z=value};
                }
            };

            struct j_byte : j_type {
                static inline const std::string sig() { return "B";}

                j_byte(const jbyte & jb = 0) : value(jb) { }

                int8_t value;

                operator int8_t() const {
                    return value;
                }

                operator unsigned char() const {
                    return value;
                }

                operator char() const {
                    return value;
                }

                operator jvalue() const {
                    return jvalue{.b=value};
                }
            };

            struct j_char : j_type {
                static inline const std::string sig() { return "C";}

                j_char(const char & v = 0) : value(v) { }
                j_char(const jchar & jc) : value(jc) { }

                char value;

                operator char() const {
                    return value;
                }

                operator unsigned short() const {
                    return value;
                }

                operator jvalue() const {
                    return jvalue{.c=static_cast<jchar>(value)};
                }
            };

            struct j_short : j_type {
                static inline const std::string sig() { return "S";}

                j_short(const jshort & js = 0) : value(js) { }

                short value;

                operator short() const {
                    return value;
                }

                operator jvalue() const {
                    return jvalue{.s=value};
                }
            };

            struct j_int : j_type {
                static inline const std::string sig() { return "I";}

                j_int(const jint & ji = 0) : value(ji) { }

                int value;

                operator int() const {
                    return value;
                }

                operator jvalue() const {
                    return jvalue{.i=value};
                }
            };

            struct j_long : j_type {
                static inline const std::string sig() { return "L";}

                j_long(const jlong & jl = 0) : value(jl) { }

                long value;

                operator long() const {
                    return value;
                }

                operator jvalue() const {
                    return jvalue{.j=value};
                }
            };

            struct j_float : j_type {
                static inline const std::string sig() { return "F";}

                j_float(const jfloat & jf = 0) : value(jf) { }

                float value;

                operator float() {
                    return value;
                }

                operator jvalue() const {
                    return jvalue{.f=value};
                }
            };

            struct j_double : j_type {
                static inline const std::string sig() { return "D";}

                j_double(const jdouble & jd = 0) : value(jd) { }

                double value;

                operator double() {
                    return value;
                }

                operator jvalue() const {
                    return jvalue{.d=value};
                }
            };
        
//            struct j_object_is_interface : std::true_type { };
//            struct j_object_is_not_interface : std::false_type { };

#if _LIBCPP_STD_VER >= 20
            template <meta::class_utility::string_literal T>
#else
            template <typename T>
#endif
            struct j_object_type : j_type {
            public:
                static inline const std::string classname() {
#if _LIBCPP_STD_VER >= 20
                    return T.value;
#else
                    if constexpr (std::is_same_v<std::remove_const_t<std::remove_reference_t<T>>, void>) {
                        return "java.lang.Object";
                    }
                    else if constexpr (std::is_same_v<std::remove_const_t<std::remove_reference_t<T>>, j_void>) {
                        return "java.lang.Object";
                    }
                    else {
                        // TODO: portablity test
                        std::string actual_class_name = meta::class_utility::classname<T>();

                        std::string define_class_name = *(meta::string::split(actual_class_name, "::").rbegin());
                        
                        auto vi = meta::string::split(define_class_name, "_");
                        if (vi.size() > 0 && (*vi.begin()) == "j") {
                            vi.erase(vi.begin());
                        } else {
                            throw "Class " + std::string(typeid(T).name()) + " parse error";
                        }
                        return meta::string::join(vi, ".");
                    }
#endif
                }

                static inline const std::string sig() {
                    return std::string("L") + meta::string::join(meta::string::split(classname(), "."), "/") + ";";
                }
                
                j_object_type(const jobject & jobj) : _jo(jobj) { }

                j_object_type();

                jobject unwrap() const {
                    return _jo;
                }

                operator jvalue() const {
                    return jvalue{.l=_jo};
                }

            protected:
                jobject _jo = nullptr;

            };
        
#if _LIBCPP_STD_VER >= 20
            using j_object = j_object_type<"java.lang.Object">;
#else
            using j_object = j_object_type<void>;
#endif

#if _LIBCPP_STD_VER >= 20
            class j_string : public j_object_type<"java.lang.String"> {
#else
            class j_java_lang_String { };
            class j_string : public j_object_type<j_java_lang_String> {
#endif
            public:

                j_string(const char * v = "");
                j_string(const std::string & v);

                
                j_string(const jstring & jstr) : _jstr(jstr) { }

                std::string value;

                operator std::string () const {
                    return value;
                }
                
                jstring unwrap() const {
                    return _jstr;
                }

                operator jvalue() const {
                    return jvalue{.l=_jstr};
                }

            private:

                jstring _jstr = nullptr;

            };



            template <typename T>
            struct j_array {
                static inline const std::string sig(){
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

            template <typename T, typename ... Args>
            struct j_types {
                static inline const std::string sig() {
                    return j_types<T>::sig() + j_types<Args...>::sig();
                }
            };

            template <typename T>
            struct j_types<T> {
                static inline const std::string sig() {
                    return T::sig();
                }
            };

            template <typename ... Args>
            static inline const std::string j_types_sig = j_types<Args...>::sig();

        
#pragma mark - jni class

            class j_env;
            class j_class {
            public:

                j_class(const jclass & cls);
                j_class(const std::string & name = "") : classname(name), sig(meta::string::join(meta::string::split(name, "."), "/")) { }

                std::string classname;
                std::string sig;

                jclass unwrap(const j_env & env) const;
            private:
                jclass _class;

            };
        

//#pragma mark - jni native method
//            class j_native_method {
//            public:
//                j_native_method(const std::string & name = "", const std::string & sig = "", void * func_ptr = nullptr) :
//                _name(name), _sig(sig), _func_ptr(func_ptr) { }
//
//                operator JNINativeMethod() const {
//                    return JNINativeMethod {
//                        (char *)_name.c_str(),
//                        (char *)_sig.c_str(),
//                        _func_ptr
//                    };
//                }
//
//                std::string id() const {
//                    return _name + _sig;
//                }
//
//            private:
//                std::string _name;
//                std::string _sig;
//                void * _func_ptr;
//            };

        
//            class j_class_native_methods {
//            public:
//                j_class_native_methods(const std::string & classname = "") : _classname(classname) { }
//
//                std::unordered_map<std::string, j_native_method> registed_native_method_id_map;
//            private:
//                std::string _classname;
//            };
            
        
#pragma mark - jni env

            class j_env {
            public:
                j_env(JNIEnv * env = nullptr) : _env(env) { }

                JNIEnv * unwrap() const {
                    return _env;
                }
                
                jclass find_class(const std::string & name) const {
                    return _env->FindClass(name.c_str());
                }
                
                jobject new_global_ref(const jobject & jobj) const {
                    return _env->NewGlobalRef(jobj);
                }
                
                void delete_global_ref(const jobject & jobj) const {
                    _env->DeleteGlobalRef(jobj);
                }
                
                jobject new_local_ref(const jobject & jobj) const {
                    return _env->NewLocalRef(jobj);
                }
                
                void delete_local_ref(const jobject & jobj) const {
                    _env->DeleteLocalRef(jobj);
                }
                
                bool exception_check() const {
                    return _env->ExceptionCheck();
                }
                
                jstring new_string_utf(const std::string & str) const {
                    return _env->NewStringUTF(str.c_str());
                }
                
                const char * get_string_utf_chars(const jstring & jstr) const {
                    return _env->GetStringUTFChars(jstr, nullptr);
                }
                
                
                jmethodID get_method_id(const jclass & jcls, const std::string & method_name, const std::string & method_sig) const {
                    return _env->GetMethodID(jcls, method_name.c_str(), method_sig.c_str());
                }
                
                jmethodID get_static_method_id(const jclass & jcls, const std::string & method_name, const std::string & method_sig) const {
                    return _env->GetStaticMethodID(jcls, method_name.c_str(), method_sig.c_str());
                }
                
                jobject new_object(const jclass & jcls, const jmethodID & jmethod) const {
                    return _env->NewObject(jcls, jmethod);
                }
                
                bool is_same_object(const jobject & lhs, const jobject & rhs) const {
                    return _env->IsSameObject(lhs, rhs);
                }

                jsize get_array_length(const jobjectArray & joa) const {
                    return _env->GetArrayLength(joa);
                }
                
                jobject get_object_array_element(const jobjectArray & joa, jint index) const {
                    return _env->GetObjectArrayElement(joa, index);
                }
                
                jclass get_object_class(const jobject & jobj) const {
                    return _env->GetObjectClass(jobj);
                }
                
                j_void call_static_void_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    _env->CallStaticVoidMethodA(jcls, jmethod, args);
                    return j_void::placeholder();
                }

                j_void call_void_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    _env->CallVoidMethodA(jobj, jmethod, args);
                    return j_void::placeholder();
                }

                j_boolean call_static_boolean_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallStaticBooleanMethodA(jcls, jmethod, args);
                }

                j_boolean call_boolean_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallBooleanMethodA(jobj, jmethod, args);
                }

                j_byte call_static_byte_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallStaticByteMethodA(jcls, jmethod, args);
                }

                j_byte call_byte_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallByteMethodA(jobj, jmethod, args);
                }

                j_byte call_static_char_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallStaticCharMethodA(jcls, jmethod, args);
                }

                j_byte call_char_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallCharMethodA(jobj, jmethod, args);
                }

                j_short call_static_short_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallStaticShortMethodA(jcls, jmethod, args);
                }

                j_short call_short_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallShortMethodA(jobj, jmethod, args);
                }

                j_int call_static_int_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallStaticIntMethodA(jcls, jmethod, args);
                }

                j_int call_int_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallIntMethodA(jobj, jmethod, args);
                }

                j_long call_static_long_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallStaticLongMethodA(jcls, jmethod, args);
                }

                j_long call_long_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallLongMethodA(jobj, jmethod, args);
                }

                j_float call_static_float_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallStaticFloatMethodA(jcls, jmethod, args);
                }

                j_float call_float_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallFloatMethodA(jobj, jmethod, args);
                }

                j_double call_static_double_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallStaticDoubleMethodA(jcls, jmethod, args);
                }

                j_double call_double_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallDoubleMethodA(jobj, jmethod, args);
                }

                j_string call_static_string_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    return (jstring)_env->CallStaticObjectMethodA(jcls, jmethod, args);
                }

                j_string call_string_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    return (jstring)_env->CallObjectMethodA(jobj, jmethod, args);
                }

                j_object call_static_object_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallStaticObjectMethodA(jcls, jmethod, args);
                }

                j_object call_object_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
                    return _env->CallObjectMethodA(jobj, jmethod, args);
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

                void load(JavaVM * vm) {
                    j_vm::shared()._vm = vm;
                    

                }

                void unload() {
                    j_env _env = env();
                    for (auto & [k,v] : jclass_pointer_map) {
                        _env.delete_global_ref((jobject)v);
                    }
                    jclass_pointer_map.clear();

                    for (auto & [k,v] : jmethod_id_pointer_map) {
                        _env.delete_global_ref((jobject)v);
                    }
                    jmethod_id_pointer_map.clear();
                }


                j_env env() {
                    JNIEnv * _env;
                    jint ret = _vm->GetEnv(reinterpret_cast<void**>(&_env), JNI_VERSION_1_6);
                    if (ret == JNI_EDETACHED) {
#ifdef Xcode
                        if (_vm->AttachCurrentThread(reinterpret_cast<void**>(&_env), nullptr) >= 0)
#else
                        if (_vm->AttachCurrentThread(&_env, nullptr) >= 0)
#endif
                        {
                            return j_env(_env);
                        }
                    }
                    return j_env(_env);
                }

            private:
                j_vm() { }
                JavaVM * _vm;

            };






#pragma mark - jni function/static function

            template <typename R, typename ... Args>
            class j_method {
            private:

#if DEBUG_ENABLED
                class _debug_j_arg_placeholder {
                    _debug_j_arg_placeholder() = delete;
                };

                using _debug_variant_type = std::conditional_t<
                        sizeof...(Args) == 0,
                        std::variant<_debug_j_arg_placeholder>,
                        std::variant<Args...>>;

                std::vector<_debug_variant_type> _debug_vvt;
#endif


            public:

                static_assert(
                        meta::arg::is::all_base_of_v<j_type, R, Args...> &&
                        !meta::arg::is::any_const_v<R, Args...> &&
                        !meta::arg::is::any_reference_v<R, Args...> &&
                        !meta::arg::is::any_pointer_v<R, Args...>,
                        "Unsupported basic types, try j_type");


                static_assert([](){
                    if constexpr (sizeof...(Args) == 0) {
                        return true;
                    } else {
                        return !meta::arg::is::any_base_of_v<j_void, Args...>;
                    }
                }(), "Parameters can not be j_void");

//                static_assert(!is_j_array_t<R>, "Return type can not be an array");   // TODO: add jobjectarray

                static inline const std::string args_sig() {
                    if constexpr (sizeof...(Args) == 0) {
                        return "";
                    } else {
                        return j_types_sig<Args...>;
                    }
                };

                static inline const std::string method_sig() {
                    std::string _s = "(";
                    _s += args_sig();
                    _s += ")";
                    _s += R::sig();
                    return _s;
                };


                j_method(const std::string & classname = "", const std::string & method_name = "", const Args & ... args) : _jcls(classname), method_name(method_name) {

                    int index = 0;
                    (void)std::initializer_list<nullptr_t>{
                            ([this, &index, &args] {
                                _jvs[index] = jvalue(args);
                                index++;

#if DEBUG_ENABLED
                                using T0 = std::remove_cvref_t<decltype(args)>;
                                constexpr int arg_index = meta::arg::index_of<T0, Args...>::index;
                                if constexpr (arg_index >= 0) {
                                    _debug_vvt.emplace_back(_debug_variant_type(std::in_place_index<arg_index>, args));
                                } else {
                                    _debug_vvt.emplace_back(_debug_variant_type(args));
                                }
#endif

                            }(), nullptr)...
                    };
                }


                inline std::string fullname() const {
                    std::string _fn = "<" + _jcls.classname + "> ";
                    _fn += R::sig();
                    _fn += " ";
                    _fn += method_name;
                    _fn += "(";
                    _fn += args_sig();
                    _fn += ");";
                    return _fn;
                };

                
                R call(const j_env & je, const j_object & jo) {
                    jobject jobj = jo.unwrap();
                    jmethodID jmethod = unwrap(je);

                    R r;
                    if constexpr (std::is_same_v<R, j_void>) {
                        je.call_void_method(jobj, jmethod, _jvs);
                        if (je.exception_check()) throw "Call java method error";
                        return j_void::placeholder();
                    }
                    else if constexpr (std::is_same_v<R, j_boolean>) {
                        r = je.call_boolean_method(jobj, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_byte>) {
                        r = je.call_byte_method(jobj, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_char>) {
                        r = je.call_char_method(jobj, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_short>) {
                        r = je.call_short_method(jobj, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_int>) {
                        r = je.call_int_method(jobj, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_long>) {
                        r = je.call_long_method(jobj, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_float>) {
                        r = je.call_float_method(jobj, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_double>) {
                        r = je.call_double_method(jobj, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_string>) {
//                        const char * str = je.get_string_utf_chars(js);
                        r = je.call_string_method(jobj, jmethod, _jvs);
                    }
                    else if constexpr (std::is_base_of_v<j_object, R>) {
                        r = je.call_object_method(jobj, jmethod, _jvs);
                    }

                    if (je.exception_check()) throw "Call java method error";

                    return r;
                }

                virtual jmethodID unwrap(const j_env & je) {
                    if (jmethod_id_pointer_map.contains(fullname()))
                    {
                        return jmethod_id_pointer_map[fullname()];
                    } else {
                        jclass jcls = _jcls.unwrap(je);
                        jmethodID jmethod_id = je.get_method_id(jcls, method_name.c_str(), method_sig().c_str());
                        if (je.exception_check()) {
                            return nullptr;
                        }
                        jmethod_id_pointer_map[fullname()] = jmethod_id;
                        return jmethod_id;
                    }
                }

                std::string method_name;

                std::string classname() const {
                    return _jcls.classname;
                };

                const j_class & jni_class() const {
                    return _jcls;
                }

            protected:

                jvalue _jvs[sizeof...(Args)];
                j_class _jcls;

            };


            template <typename R, typename ... Args>
            class j_static_method : public j_method<R, Args...> {
            public:
                using j_method<R, Args...>::j_method;

                [[maybe_unused]] R call(const j_env & je) {
                    jclass jcls = j_method<R, Args...>::_jcls.unwrap(je);
                    jmethodID jmethod = unwrap(je);

                    auto & _jvs = j_method<R, Args...>::_jvs;

                    R r;
                    if constexpr (std::is_same_v<R, j_void>) {
                        je.call_static_void_method(jcls, jmethod, _jvs);
                        if (je.exception_check()) throw "Call java method error";
                        return j_void::placeholder();
                    }
                    else if constexpr (std::is_same_v<R, j_boolean>) {
                        r = je.call_static_boolean_method(jcls, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_byte>) {
                        r = je.call_static_byte_method(jcls, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_char>) {
                        r = je.call_static_char_method(jcls, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_short>) {
                        r = je.call_static_short_method(jcls, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_int>) {
                        r = je.call_static_int_method(jcls, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_long>) {
                        r = je.call_static_long_method(jcls, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_float>) {
                        r = je.call_static_float_method(jcls, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_double>) {
                        r = je.call_static_double_method(jcls, jmethod, _jvs);
                    }
                    else if constexpr (std::is_same_v<R, j_string>) {
                        r = je.call_static_string_method(jcls, jmethod, _jvs);
                    }
                    else if constexpr (std::is_base_of_v<j_object, R>) {
                        r = je.call_static_object_method(jcls, jmethod, _jvs);
                    }

                    if (je.exception_check()) throw "Call java method error";

                    return r;
                }

                inline std::string fullname() const {
                    std::string _fn = "<" + j_method<R, Args...>::classname() + "> ";
                    _fn += "static ";
                    _fn += R::sig();
                    _fn += " ";
                    _fn += j_method<R, Args...>::method_name;
                    _fn += "(";
                    _fn += j_method<R, Args...>::args_sig();
                    _fn += ");";
                    return _fn;
                };

                jmethodID unwrap(const j_env & env) override {
                    if (jmethod_id_pointer_map.contains(fullname()))
                    {
                        return jmethod_id_pointer_map[fullname()];
                    } else {
                        jmethodID jmethod_id = env.get_static_method_id(j_method<R, Args...>::_jcls.unwrap(env),
                                                                        j_method<R, Args...>::method_name.c_str(),
                                                                        j_method<R, Args...>::method_sig().c_str());
                        if (env.exception_check()) {
                            return nullptr;
                        }
                        jmethod_id_pointer_map[fullname()] = jmethod_id;
                        return jmethod_id;
                    }
                }
            };

                
                
#if _LIBCPP_STD_VER >= 20
            template <meta::class_utility::string_literal T>
#else
            template <typename T>
#endif
            j_object_type<T>::j_object_type() {
                LOGV("sl2577 j_object init classname = %s", classname().c_str());
                const auto & env = j_vm::shared().env();
                auto jm = j_method<j_void>(classname(), "<init>");
                _jo = env.new_object(jm.jni_class().unwrap(env), jm.unwrap(env));
            }

            j_string::j_string(const char * v) : value(v) {
                _jstr = j_vm::shared().env().new_string_utf(value);
            }
        
            j_string::j_string(const std::string & v) : value(v) {
                _jstr = j_vm::shared().env().new_string_utf(value);
            }
                
            j_class::j_class(const jclass & cls) : _class(cls) {
                const auto & _env = j_vm::shared().env();
                const auto & env = _env.unwrap();
                jclass cls_wrap = _env.get_object_class(cls);
                jmethodID jm = env->GetMethodID(cls_wrap, "getName", "()Ljava/lang/String;");
                jstring jname = (jstring)env->CallObjectMethod(cls, jm);
                classname = _env.get_string_utf_chars(jname);
                sig = meta::string::join(meta::string::split(classname, "."), "/");
            }

            jclass j_class::unwrap(const j_env & env) const {
                if (jclass_pointer_map.contains(classname))
                {
                    return jclass_pointer_map[classname];
                } else {
                    jclass jcls = env.find_class(sig);
                    if (env.exception_check()) {
                        return nullptr;
                    }
                    jclass_pointer_map[classname] = (jclass)env.new_global_ref(jcls);
                    return jcls;
                }
            }

                

                
                
#pragma mark - jni helper
                


#if _LIBCPP_STD_VER >= 20
            template <typename R, typename ... Args>
            struct j_helper : j_object_type<"com.cosmojulis.meta.JniHelper"> {
#else
            class j_com_cosmojulis_meta_JniHelper { };
            template <typename R, typename ... Args>
            struct j_helper : j_object_type<j_com_cosmojulis_meta_JniHelper> {
#endif
                static auto & get_object_method_pointer_map() {
                    static auto singleton = std::unordered_map<jobject, std::function<std::conditional_t<std::is_same_v<R, j_void>, void, R>(Args...)>>();
                    return singleton;
                }
                
                j_helper(const std::function<std::conditional_t<std::is_same_v<R, j_void>, void, R>(Args...)> & func = nullptr) {
                    if (func != nullptr)
                        get_object_method_pointer_map()[_jo] = func;
                }
            };
                
                

#pragma mark - jni call

            template <typename R, typename ... Args>
            class j_static_call {
            public:
                j_static_call() { }

                j_static_call(const j_static_method<R, Args...> & sf) : _jsmethod(sf) {
                    std::cout << "call \"" << sf.fullname() << "\"" << std::endl;
                }

                j_static_call(const std::string & classname, const std::string & method_name, const Args & ... args) :
                        j_static_call(j_static_method<R, Args...>(classname, method_name, args...)) { }

                R execute() {
#ifdef Xcode
                    j_env env;
#else
                    j_env env = j_vm::shared().env();
#endif
                    return _jsmethod.call(env);
                }

            private:
                j_static_method<R, Args...> _jsmethod;
            };


            template <typename R, typename ... Args>
            class j_call {

            public:
                j_call(const j_object & jo, const j_method<R, Args...> & jm) : _jobj(jo), _jmethod(jm) {
                    std::cout << "object<" << jo.classname() << "> call: \"" << jm.fullname() << "\"" << std::endl;
                }

                j_call(const j_object & jo, const std::string & method_name, const Args & ... args) :
                        j_call(jo, j_method<R, Args...>(jo.classname(), method_name, args...)) { }

                j_call(const j_object & jo, const char * method_name, const Args & ... args) :
                        j_call(jo, std::string(method_name), args...) { }

                R execute() {
#ifdef Xcode
                    j_env env;
#else
                    j_env env = j_vm::shared().env();
#endif
                    return _jmethod.call(env, _jobj);
                }

            private:
                j_object _jobj;
                j_method<R, Args...> _jmethod;

            };

        }

    }

}



jint JNI_OnLoad(JavaVM * vm, void * reserved) {
    meta::jni::helper::j_vm::shared().load(vm);
    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM * vm, void * reserved) {
    meta::jni::helper::j_vm::shared().unload();
}

    
    
template <typename R, typename ... Args>
void find_method_pointer_callback(const meta::jni::helper::j_env & _env, const jobject & thiz, const Args & ... args) {
    auto & map = meta::jni::helper::j_helper<R, Args...>::get_object_method_pointer_map();
    
    jobject to_remove_jobj = nullptr;
    for (const auto & [k, v] : map) {
        if (_env.is_same_object(k, thiz)) {
            auto func = map[k];
            func(args...);
            to_remove_jobj = k;
            break;
        }
    }
    
    if (to_remove_jobj != nullptr) {
        map.erase(to_remove_jobj);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_meta_JniHelper_callback(JNIEnv *env, jobject thiz, jobjectArray a) {
    using namespace meta::jni::helper;
    
    auto _env = j_env(env);
    
    int count = _env.get_array_length(a);
        
    if (count == 0) {
        find_method_pointer_callback<j_void>(_env, thiz);
        return;
    }
    
    
    if (count == 1) {

        jobject jobj = _env.get_object_array_element(a, 0);
        jclass jcls = _env.get_object_class(jobj);
        j_class _jcls = j_class(jcls);
        LOGV("sl2577 jcls name: %s", _jcls.classname.c_str());

        if (_jcls.classname == "java.lang.Boolean") {
            find_method_pointer_callback<j_void, j_boolean>(_env, thiz, j_call<j_boolean>(jobj, "booleanValue").execute());
        }
        else if (_jcls.classname == "java.lang.Byte") {
            find_method_pointer_callback<j_void, j_byte>(_env, thiz, j_call<j_byte>(jobj, "byteValue").execute());
        }
        else if (_jcls.classname == "java.lang.Char") {

        }
        else if (_jcls.classname == "java.lang.Short") {

        }
        else if (_jcls.classname == "java.lang.Integer") {
            jmethodID jm = env->GetMethodID(_jcls.unwrap(env), "intValue", "()I");
            jint ji = env->CallIntMethod(jobj, jm);
            LOGV("sl2577 ji = %d", ji);
            find_method_pointer_callback<j_void, j_int>(_env, thiz, ji);
        }
        else if (_jcls.classname == "java.lang.Long") {

        }
        else if (_jcls.classname == "java.lang.Float") {

        }
        else if (_jcls.classname == "java.lang.Double") {

        }


        
//
//        if (1 == 1) {
//            auto & map = j_helper<j_void, j_int>::get_object_method_pointer_map();
//
//        }
        
        auto & map = j_helper<j_void>::get_object_method_pointer_map();
        for (const auto & [k, v] : map) {
            if (_env.is_same_object(k, thiz)) {
                auto func = map[k];
                func();
                // TODO: tag remove jo
                break;
            }
        }
        
        // remove
        return;
        
    }
        
        
    for (int i = 0; i < count; i++) {
        jobject obj = env->GetObjectArrayElement(a, i);
        jclass jcls = env->GetObjectClass(obj);
        jmethodID mid_getName = env->GetMethodID(jcls, "toString", "()Ljava/lang/String;");
        jstring name = (jstring)env->CallObjectMethod(obj, mid_getName);
        const char * str = env->GetStringUTFChars(name, nullptr);
        LOGV("sl2577 index: %d, str: %s", i, str);
    }

//    for (const auto & [k,v] : j_object_method_pointer_map) {
//        if (_env.is_same_object(k, thiz)) {
//            auto fa = j_object_method_pointer_map[k];
//
//            // TODO: unpack arr to ...
//            // fa(...)
//
//            remove = k;
//            break;
//        }
//    }
//    if (remove != nullptr) {
//        j_object_method_pointer_map.erase(remove);
//        LOGV("sl2577 remove handler");
//    } else {
//        LOGV("sl2577 j_object_map_size %d", j_object_method_pointer_map.size());
//    }
    
    LOGV("sl2577 callback implement");
}





#endif /* jni_helper_hpp */
