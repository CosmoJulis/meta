#include <jni.h>
#include <string>
#include "jni_helper.hpp"
#include <variant>
#include "alog.h"

using namespace meta::jni::helper;

extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_testFromCppToJavaStaticCall(JNIEnv *env, jobject thiz) {
    auto java_static_call = j_static_call<
            j_void,
            j_int,
            j_object>(
            "com.cosmojulis.jnitestapp.MainActivity",
            "javaStaticMethod",
            5,
            j_helper<
                    j_void,
                    j_int,
                    j_string>([](int i, std::string a){
                LOGV("jnihelp callback %d, %s", i, a.c_str());
            }));

    java_static_call.execute();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_testFromCppToJavaCall(JNIEnv *env, jobject thiz,
                                                                  jobject m) {
    auto jc = j_call<
            j_void,
            j_int,
            j_object>(
            m,
            "javaMethod",
            5,
            j_helper<
                    j_void,
                    j_int,
                    j_string>([](int i, std::string a){
                LOGV("jnihelp callback %d, %s", i, a.c_str());
            }));
    jc.execute();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_testFromJavaToCppCall(JNIEnv *env, jobject thiz, jint a,
                                                                  jobject jni) {

    auto jc = j_call<j_void, j_array<j_int, j_string>>(jni, "callback",
                                                       make_array<j_int, j_string>(a, "hello world"));
    jc.execute();
}