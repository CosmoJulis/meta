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
    auto jsc = j_static_call<j_void, j_int, j_object>("com.cosmojulis.jnitestapp.MainActivity", "javaMethod", 5, j_helper<j_void, j_int, j_string>([](int i, std::string a){
        LOGV("sl2577 jhelp callback %d, %s", i, a.c_str());
    }));
    jsc.execute();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_testClassTest(JNIEnv *env, jobject thiz) {
    auto jc = j_call<j_void, j_int, j_object>(j_base_object("com.cosmojulis.jnitestapp.TestClass"), "javaMethod", 5, j_helper<j_void, j_int, j_string>([](int i, std::string a){
        LOGV("sl2577 jhelp callback %d, %s", i, a.c_str());
    }));
    jc.execute();
}




extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_test__I_3Ljava_lang_Object_2Lcom_cosmojulis_meta_JniInterface_2(
        JNIEnv *env, jobject thiz, jint a, jobjectArray arr, jobject jhi) {
    LOGV("sl2577 i = %d", a);

    j_object jo = j_object(jhi);
    LOGV("sl2577 jo classname = %s", jo.classname().c_str());
    auto jc = j_call<j_void, j_array<j_int, j_double, j_string>>(j_object(jhi), "callback", arr);
    jc.execute();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_test__ILcom_cosmojulis_meta_JniInterface_2(JNIEnv *env,
                                                                                       jobject thiz,
                                                                                       jint a,
                                                                                       jobject jhi) {
    LOGV("sl2577 i = %d", a);
    j_object jo = j_object(jhi);
    LOGV("sl2577 jo classname = %s", jo.classname().c_str());
    // TODO: make arr object
    auto jc = j_call<j_void, j_array<j_int, j_double, j_string>>(j_object(jhi), "callback", arr);
    jc.execute();
}