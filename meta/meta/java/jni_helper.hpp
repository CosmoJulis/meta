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

#ifdef Xcode
#include <variant>
#include <unordered_map>
#include "jni.h"
#include "utility.hpp"
#include "arg.hpp"
#define LOGV(...)
#else
#include <cxxabi.h>
#include <variant>
#include <unordered_map>
#include <jni.h>
#include "utility.hpp"
#include "arg.hpp"
#include <iostream>
#include "alog.h"
#endif



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
                
                bool register_natives(const jclass & jcls, const JNINativeMethod * methods, jint count) const {
                    return _env->RegisterNatives(jcls, methods, count) == JNI_OK;
                }
                
                bool unregister_natives(const jclass & jcls) {
                    return _env->UnregisterNatives(jcls) == JNI_OK;
                }
                
                void call_void_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) {
                    _env->CallVoidMethodA(jobj, jmethod, args);
                }
                
                void call_static_void_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) {
                    _env->CallStaticVoidMethodA(jcls, jmethod, args);
                }
                
//                j_boolean call_boolean_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) {
//                    
//                }
//                void call_boolean_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) {
//                }
//                void call_boolean_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) {
//                }
//                void call_boolean_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) {
//                void call_boolean_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) {
//                void call_boolean_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) {
//                void call_boolean_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) {
//                void call_boolean_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) {

                
//            else if constexpr (std::is_same_v<R, j_boolean>) {
//                jboolean jb = env->CallBooleanMethodA(jobj, jmethod, _jvs);
//                r = j_boolean(jb);
//            }
//            else if constexpr (std::is_same_v<R, j_byte>) {
//                jbyte jb = env->CallByteMethodA(jobj, jmethod, _jvs);
//                r = j_byte(jb);
//            }
//            else if constexpr (std::is_same_v<R, j_char>) {
//                jchar jc = env->CallCharMethodA(jobj, jmethod, _jvs);
//                r = j_char(jc);
//            }
//            else if constexpr (std::is_same_v<R, j_short>) {
//                jshort js = env->CallShortMethodA(jobj, jmethod, _jvs);
//                r = j_short(js);
//            }
//            else if constexpr (std::is_same_v<R, j_int>) {
//                jint ji = env->CallIntMethodA(jobj, jmethod, _jvs);
//                r = j_int(ji);
//            }
//            else if constexpr (std::is_same_v<R, j_long>) {
//                jlong jl = env->CallLongMethodA(jobj, jmethod, _jvs);
//                r = j_long(jl);
//            }
//            else if constexpr (std::is_same_v<R, j_float>) {
//                jfloat jf = env->CallFloatMethodA(jobj, jmethod, _jvs);
//                r = j_float(jf);
//            }
//            else if constexpr (std::is_same_v<R, j_double>) {
//                jdouble jd = env->CallDoubleMethodA(jobj, jmethod, _jvs);
//                r = j_double(jd);
//            }
//            else if constexpr (std::is_same_v<R, j_string>) {
//                jstring js = (jstring)env->CallObjectMethodA(jobj, jmethod, _jvs);
//                const char * str = je.get_string_utf_chars(js);
//                r = j_string(str);
//            }
//            else if constexpr (std::is_base_of_v<j_object, R>) {
//                jobject jo = env->CallObjectMethodA(jobj, jmethod, _jvs);
                
                

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




#pragma mark - jni class

            class j_class {
            public:

                j_class(const std::string & name = "") : classname(name), sig(meta::string::join(meta::string::split(name, "."), "/")) { }

                std::string classname;
                std::string sig;

                jclass unwrap(const j_env & env) const {
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
            };

#pragma mark - jni type

            struct j_type {
                static inline const std::string sig();
            };

            struct j_void : j_type {
                static inline const std::string sig() { return "V";}
            };

            struct j_boolean : j_type {
                static inline const std::string sig() { return "Z";}

                j_boolean(const bool & v = false) : value(v) { }
                j_boolean(const unsigned char & v = 0) : value(v) { }

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

                j_byte(const int8_t & v = 0) : value(v) { }

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

                j_short(const short & v = 0) : value(v) { }

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

                j_int(const int & v = 0) : value(v) { }

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

                j_long(const long & v = 0) : value(v) { }

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

                j_float(const float & v = 0) : value(v) { }

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

                j_double(const double & v = 0) : value(v) { }

                double value;

                operator double() {
                    return value;
                }

                operator jvalue() const {
                    return jvalue{.d=value};
                }
            };

            template <typename T = void>
            struct j_object_type : j_type {
            public:
                static inline std::string classname() {
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
                        if (vi.size() > 0) {
                            vi.erase(vi.begin());
                        } else {
                            throw "Class " + std::string(typeid(T).name()) + " parse error";
                        }
                        return meta::string::join(vi, ".");
                    }
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

            private:
                jobject _jo = nullptr;

            };
        
            using j_object = j_object_type<void>;

            class j_java_lang_String { };
            class j_string : public j_object_type<j_java_lang_String> {
            public:

                j_string(const char * v = "") : value(v) {
                    _jstr = j_vm::shared().env().new_string_utf(value);
                }

                j_string(const std::string & v) : value(v) {
                    _jstr = j_vm::shared().env().new_string_utf(value);
                }

                std::string value;

                operator std::string () const {
                    return value;
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



/*
 * TODO:
 *      template<>
 *      j_method().wrap(Args.... args);
 */
#pragma mark - jni function/static function

            template <typename R, typename ... Args>
            class j_method {
            private:

#if DEBUG_ENABLED
                class _debug_j_arg_placeholder {
                    _debug_j_arg_placeholder() { }
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

//                static_assert(!is_j_array_t<R>, "Return type can not be an array");   // TODO: fix jobjectarray

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
                    JNIEnv * env = je.unwrap();
                    jobject jobj = jo.unwrap();
                    jmethodID jmethod = unwrap(je);

                    R r;
                    if constexpr (std::is_same_v<R, j_void>) {
                        je.call_void_method(jobj, jmethod, _jvs);
                        if (je.exception_check()) throw "Call java method error";
                        return j_void();
                    }
                    else if constexpr (std::is_same_v<R, j_boolean>) {
                        jboolean jb = env->CallBooleanMethodA(jobj, jmethod, _jvs);
                        r = j_boolean(jb);
                    }
                    else if constexpr (std::is_same_v<R, j_byte>) {
                        jbyte jb = env->CallByteMethodA(jobj, jmethod, _jvs);
                        r = j_byte(jb);
                    }
                    else if constexpr (std::is_same_v<R, j_char>) {
                        jchar jc = env->CallCharMethodA(jobj, jmethod, _jvs);
                        r = j_char(jc);
                    }
                    else if constexpr (std::is_same_v<R, j_short>) {
                        jshort js = env->CallShortMethodA(jobj, jmethod, _jvs);
                        r = j_short(js);
                    }
                    else if constexpr (std::is_same_v<R, j_int>) {
                        jint ji = env->CallIntMethodA(jobj, jmethod, _jvs);
                        r = j_int(ji);
                    }
                    else if constexpr (std::is_same_v<R, j_long>) {
                        jlong jl = env->CallLongMethodA(jobj, jmethod, _jvs);
                        r = j_long(jl);
                    }
                    else if constexpr (std::is_same_v<R, j_float>) {
                        jfloat jf = env->CallFloatMethodA(jobj, jmethod, _jvs);
                        r = j_float(jf);
                    }
                    else if constexpr (std::is_same_v<R, j_double>) {
                        jdouble jd = env->CallDoubleMethodA(jobj, jmethod, _jvs);
                        r = j_double(jd);
                    }
                    else if constexpr (std::is_same_v<R, j_string>) {
                        jstring js = (jstring)env->CallObjectMethodA(jobj, jmethod, _jvs);
                        const char * str = je.get_string_utf_chars(js);
                        r = j_string(str);
                    }
                    else if constexpr (std::is_base_of_v<j_object, R>) {
                        jobject jo = env->CallObjectMethodA(jobj, jmethod, _jvs);
                        r = j_object(jo);
                    }

                    if (je.exception_check()) throw "Call java method error";

                    return r;
                }

                jmethodID unwrap(const j_env & env) {
                    if (jmethod_id_pointer_map.contains(fullname()))
                    {
                        return jmethod_id_pointer_map[fullname()];
                    } else {
                        jclass jcls = _jcls.unwrap(env);
                        jmethodID jmethod_id = env.get_method_id(jcls, method_name.c_str(), method_sig().c_str());
                        if (env.exception_check()) {
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

                R call(const j_env & je) {
                    JNIEnv * env = je.unwrap();
                    jclass jcls = j_method<R, Args...>::_jcls.unwrap(env);
                    jmethodID jmethod = unwrap(je);

                    auto & _jvs = j_method<R, Args...>::_jvs;

                    R r;
                    if constexpr (std::is_same_v<R, j_void>) {
                        env->CallStaticVoidMethodA(jcls, jmethod, _jvs);
                        if (je.exception_check()) throw "Call java method error";
                        return j_void();
                    }
                    else if constexpr (std::is_same_v<R, j_boolean>) {
                        jboolean jb = env->CallStaticBooleanMethodA(jcls, jmethod, _jvs);
                        r = j_boolean(jb);
                    }
                    else if constexpr (std::is_same_v<R, j_byte>) {
                        jbyte jb = env->CallStaticByteMethodA(jcls, jmethod, _jvs);
                        r = j_byte(jb);
                    }
                    else if constexpr (std::is_same_v<R, j_char>) {
                        jchar jc = env->CallStaticCharMethodA(jcls, jmethod, _jvs);
                        r = j_char(jc);
                    }
                    else if constexpr (std::is_same_v<R, j_short>) {
                        jshort js = env->CallStaticShortMethodA(jcls, jmethod, _jvs);
                        r = j_short(js);
                    }
                    else if constexpr (std::is_same_v<R, j_int>) {
                        jint ji = env->CallStaticIntMethodA(jcls, jmethod, _jvs);
                        r = j_int(ji);
                    }
                    else if constexpr (std::is_same_v<R, j_long>) {
                        jlong jl = env->CallStaticLongMethodA(jcls, jmethod, _jvs);
                        r = j_long(jl);
                    }
                    else if constexpr (std::is_same_v<R, j_float>) {
                        jfloat jf = env->CallStaticFloatMethodA(jcls, jmethod, _jvs);
                        r = j_float(jf);
                    }
                    else if constexpr (std::is_same_v<R, j_double>) {
                        jdouble jd = env->CallStaticDoubleMethodA(jcls, jmethod, _jvs);
                        r = j_double(jd);
                    }
                    else if constexpr (std::is_same_v<R, j_string>) {
                        jstring js = (jstring)env->CallStaticObjectMethodA(jcls, jmethod, _jvs);
                        const char * str = je.get_string_utf_chars(js);
                        r = j_string(str);
                    }
                    else if constexpr (std::is_base_of_v<j_object, R>) {
                        jobject jo = env->CallStaticObjectMethodA(jcls, jmethod, _jvs);
                        r = j_object(jo);
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

                jmethodID unwrap(const j_env & env) {
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


#pragma mark - jni interface callback
            template <typename T>
            j_object_type<T>::j_object_type() {
                LOGV("sl2577 j_object init classname = %s", classname().c_str());
                const auto & env = j_vm::shared().env();
                auto jm = j_method<j_void>(classname(), "<init>");
                _jo = env.new_object(jm.jni_class().unwrap(env), jm.unwrap(env));
            }


            class j_com_cosmojulis_meta_JniHelperInterface { };
        
            template <typename R, typename ... Args>
            struct j_interface : j_object_type<j_com_cosmojulis_meta_JniHelperInterface> {

                static inline const std::string sig() {
                    return std::string("L") + meta::string::join(meta::string::split(classname(), "."), "/") + ";";
                }

                j_interface() {
                    LOGV("sl2577 j_interface init classname = %s", classname().c_str());
                }
                
                // TODO register native class method
                const std::string method_sig() {
                    return j_method<R, Args...>::method_sig();
                }

                // TODO register native class method
                R callback(JNIEnv * env, jobject obj) {

                }

                friend R callback(j_interface<R, Args...> & ji, JNIEnv * env, jobject obj) {
                    return ji.callback(env, obj);
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
                    std::cout << "object<" << jo.classname() << "> call: \"" << jm.fullname << "\"" << std::endl;
                }

                j_call(const j_object & jo, const std::string & method_name, const Args & ... args) :
                        j_call(jo, j_method<R, Args...>(method_name, args...)) { }

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

void registerCallback() {
    using namespace meta::jni::helper;
    auto jcls = j_class("com/cosmojulis/meta/JniHelperInterface");
    auto je = j_vm::shared().env();
    // TODO: custom jni native method class;
    JNINativeMethod methods[] = {
//        {(char *)j_interface_object::method_name.c_str(), (char *)j_interface_object::method_sig().c_str(), (void *)j_interface_object::callback}
    };

    je.register_natives(jcls.unwrap(je), methods, sizeof(methods)/sizeof(methods[0]));
}

jint JNI_OnLoad(JavaVM * vm, void * reserved) {
    meta::jni::helper::j_vm::shared().load(vm);
    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM * vm, void * reserved) {
    meta::jni::helper::j_vm::shared().unload();
}






#endif /* jni_helper_hpp */
