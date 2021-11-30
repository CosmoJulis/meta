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
//    auto jsc = j_static_call<j_void, j_object>("com.cosmojulis.jnitestapp.MainActivity", "javaMethod", j_interface<j_void, j_int>([](int a){
//        LOGV("sl2577 jhelp callback %d", a);
//    }));
    auto jsc = j_static_call<j_void, j_object>("com.cosmojulis.jnitestapp.MainActivity", "javaMethod", j_interface<j_void, j_int, j_string, j_double>([](int i, std::string a, double d){
        LOGV("sl2577 jhelp callback %d, %s, %lf", i, a.c_str(), d);
    }));
    jsc.execute();

//    const char * jniclsname = "com/cosmojulis/jnitestapp/MainActivity";
//    jclass  jc = env->FindClass(jniclsname);
//
//    jmethodID jm = env->GetStaticMethodID(jc, "javaMethod",
//                                          "(Lcom/cosmojulis/meta/JniHelperInterface;)V");
//
//
//    jclass jh = env->FindClass("com/cosmojulis/meta/JniHelper");
//    jmethodID nm = env->GetMethodID(jh, "<init>", "()V");
//    jobject jhobj = env->NewObject(jh, nm);
//
//    env->CallStaticVoidMethod(jc, jm, jhobj);


}

