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



namespace meta::jni::helper {

#pragma mark - jni jclass jmethodid cached

    static std::unordered_map<std::string, jclass> jclass_pointer_map;
    static std::unordered_map<std::string, jmethodID> jmethod_id_pointer_map;


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

        virtual inline const std::string classname() const {
            return "java.lang.Boolean";
        }

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

        virtual inline const std::string classname() const {
            return "java.lang.Byte";
        }

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

        virtual inline const std::string classname() const {
            return "java.lang.Character";
        }

        j_char(const char & v) : value(v) { }
        j_char(const jchar & jc = 0) : value(jc) { }

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

        virtual inline const std::string classname() const {
            return "java.lang.Short";
        }

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

        virtual inline const std::string classname() const {
            return "java.lang.Integer";
        }

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

        virtual inline const std::string classname() const {
            return "java.lang.Long";
        }

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

        virtual inline const std::string classname() const {
            return "java.lang.Float";
        }

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

        virtual inline const std::string classname() const {
            return "java.lang.Double";
        }

        j_double(const jdouble & jd = 0) : value(jd) { }

        double value;

        operator double() const {
            return value;
        }

        operator jvalue() const {
            return jvalue{.d=value};
        }
    };

    class j_string;
    struct j_base_object : j_type {
    public:
        virtual inline const std::string classname() const {
            return _classname;
        }

        virtual inline const std::string sig() const {
            return std::string("L") + meta::string::join(meta::string::split(classname(), "."), "/") + ";";
        }

        j_base_object(const jobject & jobj);

        j_base_object(const std::string & name = "java.lang.Object");

        jobject unwrap() const {
            return _jo;
        }

        operator jobject() const {
            return _jo;
        }

        operator j_string() const;

        operator jvalue() const {
            return jvalue{.l=_jo};
        }

    protected:
        std::string _classname;
        jobject _jo = nullptr;
    };


    using j_object = j_base_object;


#if _LIBCPP_STD_VER >= 20
    template <meta::class_utility::string_literal T>
#else
    template <typename T>
#endif
    class j_derive_object : public j_base_object {
    public:

//#if _LIBCPP_STD_VER >= 20
//    static inline const meta::class_utility::string_literal literal = T;
//#else
//    typedef T value_type;
//#endif

        j_derive_object() : j_base_object(classname()) { }

        j_derive_object(const jobject & jobj) : j_base_object(jobj) {
            _classname = classname();
        }


        inline const std::string classname() const override {
            return get_classname();
        }

        static inline const std::string get_classname() {
#if _LIBCPP_STD_VER >= 20
            return T.value;
#else
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
#endif
        }
    };


//template <typename T>
//struct is_j_derive_object {
//
//    template <typename _T>
//    struct _impl : std::false_type { };
//
//#if _LIBCPP_STD_VER >= 20
//    template <meta::class_utility::string_literal _T>
//#else
//    template <typename _T>
//#endif
//    struct _impl<j_derive_object<_T>> : std::true_type { };
//
//    static inline constexpr bool value = _impl<T>::value;
//};







#if _LIBCPP_STD_VER >= 20
    class j_string : public j_derive_object<"java.lang.String">
#else
    class j_java_lang_String { };
    class j_string : public j_derive_object<j_java_lang_String>
#endif
    {
    public:

        j_string(const char * v = "");
        j_string(const std::string & v);


        j_string(const jstring & jstr);

        std::string value;

        operator std::string () const {
            return value;
        }

        jstring unwrap() const {
            return (jstring)_jo;
        }

        operator jvalue() const {
            return jvalue{.l=_jo};
        }
    };

    class j_java_lang_Array { };

    template <typename T>
#if _LIBCPP_STD_VER >= 20
    class j_base_array : public j_derive_object<"java.lang.Array">
#else
    class j_base_array : public j_derive_object<j_java_lang_Array>
#endif
    {
    public:
        static_assert(std::is_base_of_v<j_type, T>, "Not an jtype.");

        inline const std::string sig() const override {
            if constexpr (std::is_same_v<T, j_base_object>) {
                return "[Ljava/lang/Object;";
            }
            else if constexpr (std::is_base_of_v<j_base_object, T>) {
                return std::string("[L") + meta::string::join(meta::string::split(T::get_classname(), "."), "/") + ";";
            }
            else {
                return "[" + T::sig();
            }
        }


#if _LIBCPP_STD_VER >= 20
        j_base_array(const jobject & jobj) : j_derive_object<"java.lang.Array">(jobj) { }

        j_base_array(const jobjectArray & jarr) : j_derive_object<"java.lang.Array">(jarr) { }

        template <typename ... Args>
        j_base_array(const Args & ... args) : j_derive_object<"java.lang.Array">(make_array(args...)) { }

#else
        j_base_array(const jobject & jobj) : j_derive_object<j_java_lang_Array>(jobj) { }

        j_base_array(const jobjectArray & jarr) : j_derive_object<j_java_lang_Array>(jarr) { }

        template <typename ... Args>
        j_base_array(const Args & ... args) : j_derive_object<j_java_lang_Array>(make_array(args...)) { }
#endif

    };



    template <typename ... Args>
    using j_array = std::conditional_t<meta::arg::is::all_same_v<Args...>, j_base_array<typename meta::arg::of<0, Args...>::type>, j_base_array<j_base_object>>;


    /* j_array TODO
     * j_array<T> same class [T
     * j_array<T, Args...> not same class [java/lang/Object;
     */

    //            template <typename T>
    //            struct j_array {
    //                static inline const std::string sig(){
    //                    return std::string("[") + T::sig();
    //                }
    //
    //                using value_type = T;
    //
    //                template <typename E>
    //                j_array(const std::vector<E> & vv) { // TODO: vector to iterable
    //                    for (const E & v : vv) {
    //                        values.push_back(value_type(v));
    //                    }
    //                }
    //
    //                std::vector<value_type> values;
    //            };
    //
    //
    //            template <typename T>
    //            struct is_j_array {
    //                static inline constexpr bool value = false;
    //            };
    //
    //            template <typename T>
    //            struct is_j_array<j_array<T>> {
    //                static inline constexpr bool value = true;
    //            };
    //
    //            template <typename T>
    //            inline constexpr bool is_j_array_t = is_j_array<T>::value;



    template <typename T, typename ... Args>
    struct j_types {
        static inline const std::string sig(const T & t, const Args & ... args) {
            return j_types<T>::sig(t) + j_types<Args...>::sig(args...);
        }
    };

    template <typename T>
    struct j_types<T> {
        static inline const std::string sig(const T & t) {
            if constexpr (std::is_base_of_v<j_base_object, std::remove_cvref_t<T>>) {
                return t.sig();
            } else {
                return T::sig();
            }
        }
    };

    template <typename ... Args>
    static inline const std::string j_types_sig(const Args & ... args) {
        return j_types<Args...>::sig(args...);
    }


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

        jobject  new_object(const jclass & jcls, const jmethodID & jmethod, const jvalue & jval) const {
            return _env->NewObjectA(jcls, jmethod, &jval);
        }

        bool is_same_object(const jobject & lhs, const jobject & rhs) const {
            return _env->IsSameObject(lhs, rhs);
        }

        jobjectArray new_object_array(const size_t & len, const jclass & jcls, const jobject & obj) const {
            return _env->NewObjectArray((jsize)len, jcls, obj);
        }

        void set_object_array_element(const jobjectArray & arr, const size_t & index, jobject val) const {
            _env->SetObjectArrayElement(arr, (jsize)index, val);
        }

        size_t get_array_length(const jobjectArray & joa) const {
            return _env->GetArrayLength(joa);
        }

        jobject get_object_array_element(const jobjectArray & joa, jint index) const {
            return _env->GetObjectArrayElement(joa, index);
        }

        jclass get_object_class(const jobject & jobj) const {
            return _env->GetObjectClass(jobj);
        }

        const std::string get_object_classname(const jobject & jobj) const {
            jclass jcls = get_object_class(jobj);
            jclass cls_class = find_class("java/lang/Class");
            jmethodID jm = _env->GetMethodID(cls_class, "getName", "()Ljava/lang/String;");
            jstring classname = (jstring)_env->CallObjectMethod(jcls, jm);
            return get_string_utf_chars(classname);
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

        j_char call_static_char_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
            return _env->CallStaticCharMethodA(jcls, jmethod, args);
        }

        j_char call_char_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
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

        j_base_object call_static_object_method(const jclass & jcls, const jmethodID & jmethod, const jvalue * args) const {
            return _env->CallStaticObjectMethodA(jcls, jmethod, args);
        }

        j_base_object call_object_method(const jobject & jobj, const jmethodID & jmethod, const jvalue * args) const {
            return _env->CallObjectMethodA(jobj, jmethod, args);
        }

        template <typename T>
        jobject get_object(const T & t) const {
            static_assert(
                    meta::arg::is::all_base_of_v<j_type, T>, "Unsupported basic types, try j_type");
            static_assert(!std::is_same_v<j_void, T>, "Unsupported j_void");

            const auto & cls_name = t.classname();
            const auto & cls = find_class(meta::string::join(meta::string::split(cls_name, "."), "/"));

            if constexpr (std::is_same_v<j_boolean, T>) {
                const auto & mtd = get_method_id(cls, "<init>", "(Z)V");
                return new_object(cls, mtd, j_boolean(t));
            }
            else if constexpr (std::is_same_v<j_byte, T>) {
                const auto & mtd = get_method_id(cls, "<init>", "(B)V");
                return new_object(cls, mtd, j_byte(t));
            }
            else if constexpr (std::is_same_v<j_char, T>) {
                const auto & mtd = get_method_id(cls, "<init>", "(C)V");
                return new_object(cls, mtd, j_char(t));
            }
            else if constexpr (std::is_same_v<j_short, T>) {
                const auto & mtd = get_method_id(cls, "<init>", "(S)V");
                return new_object(cls, mtd, j_short(t));
            }
            else if constexpr (std::is_same_v<j_int, T>) {
                const auto & mtd = get_method_id(cls, "<init>", "(I)V");
                return new_object(cls, mtd, j_int(t));
            }
            else if constexpr (std::is_same_v<j_long, T>) {
                const auto & mtd = get_method_id(cls, "<init>", "(L)V");
                return new_object(cls, mtd, j_long(t));
            }
            else if constexpr (std::is_same_v<j_float, T>) {
                const auto & mtd = get_method_id(cls, "<init>", "(F)V");
                return new_object(cls, mtd, j_float(t));
            }
            else if constexpr (std::is_same_v<j_double, T>) {
                const auto & mtd = get_method_id(cls, "<init>", "(D)V");
                return new_object(cls, mtd, j_double(t));
            }
            else if constexpr (std::is_same_v<j_string, T>) {
                return t;
            }
            else {
                return t;
            }
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
            j_env m_env = this->env();
            for (auto & [k,v] : jclass_pointer_map) {
                m_env.delete_global_ref((jobject)v);
            }
            jclass_pointer_map.clear();

            for (auto & [k,v] : jmethod_id_pointer_map) {
                m_env.delete_global_ref((jobject)v);
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


        j_method(const std::string & classname = "", const std::string & method_name = "", const Args & ... args) : _jcls(classname), method_name(method_name) {

            int index = 0;
            (void)std::initializer_list<nullptr_t>{
                    ([this, &index, &args] {
                        _jvs[index] = jvalue(args);
                        index++;

#if DEBUG_ENABLED
                        using T0 = std::remove_cvref_t<decltype(args)>;
                        constexpr int arg_index = meta::arg::index<T0, Args...>::value;
                        if constexpr (arg_index >= 0) {
                            _debug_vvt.emplace_back(_debug_variant_type(std::in_place_index<arg_index>, args));
                        } else {
                            _debug_vvt.emplace_back(_debug_variant_type(args));
                        }
#endif

                    }(), nullptr)...
            };


            if constexpr (sizeof...(Args) > 0) {
                _args_sig = j_types_sig<Args...>(args...);
            }
        }

        inline const std::string reture_sig() const {
            if constexpr (std::is_base_of_v<j_base_object, R>) {
                return "Ljava/lang/Object;";
            } else {
                return R::sig();
            }
        }

        const std::string method_sig() const {
            std::string _s = "(";
            _s += _args_sig;
            _s += ")";
            _s += reture_sig();
            return _s;
        };


        // 返回类型使用不参与构造使用 java.lang.Object
        const std::string fullname() const {
            std::string _fn = "<" + _jcls.classname + "> ";
            _fn += reture_sig();
            _fn += " ";
            _fn += method_name;
            _fn += "(";
            _fn += _args_sig;
            _fn += ");";
            return _fn;
        };


        R call(const j_env & je, const j_base_object & jo) {
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
                r = je.call_string_method(jobj, jmethod, _jvs);
            }
            else if constexpr (std::is_base_of_v<j_base_object, R>) {
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
        std::string _args_sig;

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
            else if constexpr (std::is_base_of_v<j_base_object, R>) {
                r = je.call_static_object_method(jcls, jmethod, _jvs);
            }

            if (je.exception_check()) throw "Call java method error";

            return r;
        }

        std::string fullname() const {
            std::string _fn = "<" + j_method<R, Args...>::classname() + "> ";
            _fn += "static ";
            _fn += R::sig();
            _fn += " ";
            _fn += j_method<R, Args...>::method_name;
            _fn += "(";
            _fn += j_method<R, Args...>::_args_sig;
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






#pragma mark - jni helper



#if _LIBCPP_STD_VER >= 20
    template <typename R, typename ... Args>
struct j_helper : j_derive_object<"com.cosmojulis.meta.JniHelper">
#else
    class j_com_cosmojulis_meta_JniHelper { };
    template <typename R, typename ... Args>
    struct j_helper : j_derive_object<j_com_cosmojulis_meta_JniHelper>
#endif
    {
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
            j_env m_env;
#else
            j_env m_env = j_vm::shared().env();
#endif
            return _jsmethod.call(m_env);
        }

    private:
        j_static_method<R, Args...> _jsmethod;
    };


    template <typename R, typename ... Args>
    class j_call {

    public:
        j_call(const j_base_object & jo, const j_method<R, Args...> & jm) : _jobj(jo), _jmethod(jm) {
            std::cout << "object<" << jo.classname() << "> call: \"" << jm.fullname() << "\"" << std::endl;
        }

        j_call(const j_base_object & jo, const std::string & method_name, const Args & ... args) :
                j_call(jo, j_method<R, Args...>(jo.classname(), method_name, args...)) { }

        j_call(const j_base_object & jo, const char * method_name, const Args & ... args) :
                j_call(jo, std::string(method_name), args...) { }

        R execute() {
#ifdef Xcode
            j_env m_env;
#else
            j_env m_env = j_vm::shared().env();
#endif
            return _jmethod.call(m_env, _jobj);
        }

    private:
        j_base_object _jobj;
        j_method<R, Args...> _jmethod;

    };


#pragma mark - jni delay


    template <typename ... Args>
    j_array<Args...> make_array(const Args & ... args) {
#ifndef Xcode
        size_t len = sizeof...(args);
        const auto & m_env = j_vm::shared().env();
        const jclass & elementCls = m_env.find_class(meta::string::join(meta::string::split("java.lang.Object", "."), "/"));

        jobjectArray objArr = m_env.new_object_array(len, elementCls, NULL);

        size_t index = 0;
        (void)std::initializer_list<nullptr_t>{
                ([&index, &args, &m_env, &objArr] {
                    jobject jobj = m_env.get_object(args);
                    m_env.set_object_array_element(objArr, index, jobj);
                    index++;
                }(), nullptr)...
        };
        return objArr;
#else
        j_object obj;
        return obj;
#endif
    }


    j_base_object::j_base_object(const std::string & name) : _classname(name) {
#ifndef Xcode
        const auto & m_env = j_vm::shared().env();
        auto jm = j_method<j_void>(classname(), "<init>");
        _jo = m_env.new_object(jm.jni_class().unwrap(m_env), jm.unwrap(m_env));
#endif
    }

    j_base_object::j_base_object(const jobject & jobj) : _jo(jobj) {
#ifndef Xcode
        const auto & m_env = j_vm::shared().env();
        _classname = m_env.get_object_classname(jobj);
#endif
    }

    j_base_object::operator j_string() const {
        const auto & m_env = j_vm::shared().env();
        if (m_env.get_object_classname(_jo) == "java.lang.String") {
            return j_string((jstring)_jo);
        } else {
            throw "Can not cast to jstring.";
        }
    }

    j_string::j_string(const char * v) : value(v) {
        _jo = j_vm::shared().env().new_string_utf(value);
    }

    j_string::j_string(const std::string & v) : value(v) {
        _jo = j_vm::shared().env().new_string_utf(value);
    }

    j_string::j_string(const jstring & jstr) {
        _jo = jstr;
        value = j_vm::shared().env().get_string_utf_chars(jstr);
    }


    j_class::j_class(const jclass & cls) : _class(cls) {
        classname = j_call<j_string>(cls, "getName").execute();
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


    template <typename R>
    R get_value(const jobject & jobj) {
        if constexpr (std::is_same_v<R, j_boolean>) {
            return j_call<R>(jobj, "booleanValue").execute();
        }
        else if constexpr (std::is_same_v<R, j_byte>) {
            return j_call<R>(jobj, "byteValue").execute();
        }
        else if constexpr (std::is_same_v<R, j_char>) {
            return j_call<R>(jobj, "charValue").execute();
        }
        else if constexpr (std::is_same_v<R, j_short>) {
            return j_call<R>(jobj, "shortValue").execute();
        }
        else if constexpr (std::is_same_v<R, j_int>) {
            return j_call<R>(jobj, "intValue").execute();
        }
        else if constexpr (std::is_same_v<R, j_long>) {
            return j_call<R>(jobj, "longValue").execute();
        }
        else if constexpr (std::is_same_v<R, j_float>) {
            return j_call<R>(jobj, "floatValue").execute();
        }
        else if constexpr (std::is_same_v<R, j_double>) {
            return j_call<R>(jobj, "doubleValue").execute();
        }
        else if constexpr (std::is_same_v<R, j_string>) {
            return j_string(jstring(jobj));
        }
        else {
            return j_object(jobj);
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
void find_method_pointer_callback(const meta::jni::helper::j_env & m_env, const jobject & thiz, const Args & ... args) {
    auto & map = meta::jni::helper::j_helper<R, Args...>::get_object_method_pointer_map(); // TODO: change to std::variable or std::any

    jobject to_remove_jobj = nullptr;
    for (const auto & [k, v] : map) {
        if (m_env.is_same_object(k, thiz)) {
            auto func = map[k];
            func(args...);
            to_remove_jobj = k;
            break;
        }
    }

    if (to_remove_jobj != nullptr) {
        map.erase(to_remove_jobj);
    } else {
        assert(false);
        std::cout << "Not found map func." << std::endl;
    }
}


template <int C, typename R, typename ... Args>
void magic_call(const meta::jni::helper::j_env & m_env, const jobject & thiz, const jobjectArray & a, const Args & ... args) {
    using namespace meta::jni::helper;

    if constexpr (C == 0) {
        find_method_pointer_callback<R, Args...>(m_env, thiz, args...);
    }
    else {

        jobject jobj = m_env.get_object_array_element(a, C - 1);
        std::string jobj_classname = m_env.get_object_classname(jobj);

        if (jobj_classname == "java.lang.Boolean") {
            magic_call<C - 1, R, j_boolean, Args...>(m_env, thiz, a, get_value<j_boolean>(jobj), args...);
        }
        else if (jobj_classname == "java.lang.Byte") {
            throw "Unsupported j_byte now.";
//            magic_call<C - 1, R, j_byte, Args...>(m_env, thiz, a, get_value<j_byte>(jobj), args...);
        }
        else if (jobj_classname == "java.lang.Char") {
            throw "Unsupported j_char now.";
//            magic_call<C - 1, R, j_char, Args...>(m_env, thiz, a, get_value<j_char>(jobj), args...);
        }
        else if (jobj_classname == "java.lang.Short") {
            throw "Unsupported j_short now.";
//            magic_call<C - 1, R, j_short, Args...>(m_env, thiz, a, get_value<j_short>(jobj), args...);
        }
        else if (jobj_classname == "java.lang.Integer") {
            magic_call<C - 1, R, j_int, Args...>(m_env, thiz, a, get_value<j_int>(jobj), args...);
        }
        else if (jobj_classname == "java.lang.Long") {
            magic_call<C - 1, R, j_long, Args...>(m_env, thiz, a, get_value<j_long>(jobj), args...);
        }
        else if (jobj_classname == "java.lang.Float") {
            magic_call<C - 1, R, j_float, Args...>(m_env, thiz, a, get_value<j_float>(jobj), args...);
        }
        else if (jobj_classname == "java.lang.Double") {
            magic_call<C - 1, R, j_double, Args...>(m_env, thiz, a, get_value<j_double>(jobj), args...);
        }
        else if (jobj_classname == "java.lang.String") {
            magic_call<C - 1, R, j_string, Args...>(m_env, thiz, a, get_value<j_string>(jobj), args...);
        }
        else {
            magic_call<C - 1, R, j_object, Args...>(m_env, thiz, a, get_value<j_object>(jobj), args...);
        }
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_meta_JniHelper_callback(JNIEnv *env, jobject thiz, jobjectArray a) {
    using namespace meta::jni::helper;

    auto m_env = j_env(env);

    size_t count = m_env.get_array_length(a);

#ifndef Xcode
    if (count == 0) {
        magic_call<0, j_void>(m_env, thiz, a);
        return;
    }

    if (count == 1) {
        magic_call<1, j_void>(m_env, thiz, a);
        return;
    }

    if (count == 2) {
        magic_call<2, j_void>(m_env, thiz, a);
        return;
    }

    if (count == 3) {
        magic_call<3, j_void>(m_env, thiz, a);
        return;
    }
#endif

    throw "No atuo impl args count at " + std::to_string(count);
}




#endif /* jni_helper_hpp */
