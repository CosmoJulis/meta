#include <jni.h>
#include <string>
#include "jni_helper.hpp"
#include <variant>
#include "alog.h"

using namespace meta::jni::helper;

std::string test_combine(const std::string & a, const std::string & b) {
    auto jsm = j_static_method<j_string, j_string, j_string>("com.cosmojulis.jnitestapp.MainActivity", "test_combine", a, b);
    auto jc = j_static_call(jsm);
    return jc.execute();
//    return "foo bar";
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    std::string hello = "hello world";

    return env->NewStringUTF(hello.c_str());
}




extern "C" JNIEXPORT void  JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_test(JNIEnv * env, jobject) {

    auto jsc = j_static_call<j_void, j_interface<j_void>>("com.cosmojulis.jnitestapp.MainActivity", "callback", j_interface<j_void>());
    jsc.execute();

//    auto jsm = j_static_method<j_void, j_interface<j_void>>("com.cosmojulis.jnitestapp.MainActivity", "callback", j_interface<j_void>("com.cosmojulis.meta.JniHelperInterface"));
//    LOGV("sl2577 sig = %s", decltype(jsm)::method_sig().c_str());
//    LOGV("sl2577 fullname = %s", jsm.fullname().c_str());

//    LOGV("sl2577 j_types_sig j_object = %s", j_types_sig<j_object>.c_str());
//    auto jsm = j_static_method<j_void, j_object>("com.cosmojulis.jnitestapp.MainActivity", "callback", j_object());
//    LOGV("sl2577 sig = %s", decltype(jsm)::method_sig().c_str());
//    LOGV("sl2577 fullname = %s", jsm.fullname().c_str());

}

extern "C" JNIEXPORT void  JNICALL
Java_com_cosmojulis_meta_JniHelperInterface_callback(JNIEnv * env, jobject jobject1) {
    LOGV("sl2577 JniHelperInterface callback %s", jobject1);
}