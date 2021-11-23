#include <jni.h>
#include <string>
#include "jni_helper.hpp"
#include <variant>
#include "alog.h"

using namespace meta::jni::helper;

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

}

extern "C" JNIEXPORT void  JNICALL
Java_com_cosmojulis_meta_JniHelperInterface_callback(JNIEnv * env, jobject jobject1) {
    LOGV("sl2577 JniHelperInterface callback %p", jobject1);
}