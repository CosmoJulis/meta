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



extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_test__(JNIEnv *env, jobject thiz) {
    auto jsc = j_static_call<j_void, j_object>("com.cosmojulis.jnitestapp.MainActivity", "javaMethod", j_helper<j_void, j_int, j_string>([](int i, std::string a){
        LOGV("sl2577 jhelp callback %d, %s", i, a.c_str());
    }));
    jsc.execute();
}

// TODO: array
extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_test__Lcom_cosmojulis_meta_JniInterface_2(JNIEnv *env,
                                                                                      jobject thiz,
                                                                                      jobject jhi) {
    auto jc = j_call<j_void, j_int, j_double, j_string>(j_object(jhi), "callback", 1, 0.5, "hell world");
    jc.execute();
}