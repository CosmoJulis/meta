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

    jclass jcls = env->FindClass("[Ljava/lang/Object;");
    jobjectArray jarr = env->NewObjectArray(1, jcls, NULL);
    jclass jicls = env->FindClass("java/lang/Integer");
    jmethodID jim = env->GetMethodID(jicls, "<init>", "(I)V");
    jobject jiobj = env->NewObject(jicls, jim, 10);

    env->SetObjectArrayElement(jarr, 0, jiobj);

    LOGV("sl2577 test success");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_testClassTest(JNIEnv *env, jobject thiz) {
    auto jc = j_call<j_void, j_int, j_object>(j_base_object("com.cosmojulis.jnitestapp.TestClass"), "javaMethod", 5, j_helper<j_void, j_int, j_string>([](int i, std::string a){
        LOGV("sl2577 jhelp callback %d, %s", i, a.c_str());
    }));
    jc.execute();
}




//extern "C"
//JNIEXPORT void JNICALL
//Java_com_cosmojulis_jnitestapp_MainActivity_test__I_3Ljava_lang_Object_2Lcom_cosmojulis_meta_JniInterface_2(
//        JNIEnv *env, jobject thiz, jint a, jobjectArray arr, jobject jhi) {
//    LOGV("sl2577 i = %d", a);
//
//    j_object jo = j_object(jhi);
//    LOGV("sl2577 jo classname = %s", jo.classname().c_str());
//    auto jc = j_call<j_void, j_array<j_int, j_double, j_string>>(j_object(jhi), "callback", (jobject)arr);
//    jc.execute();
//}


extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_test__IDLjava_lang_String_2Lcom_cosmojulis_meta_JniInterface_2(
        JNIEnv *env, jobject thiz, jint a, jdouble b, jstring s, jobject jhi) {
    LOGV("sl2577 i = %d", a);

    j_object jo = j_object(jhi);
    LOGV("sl2577 jo classname = %s", jo.classname().c_str());

    auto jc = j_call<j_void, j_array<j_int, j_double, j_string>>(j_object(jhi), "callback",
                                                                 make_array<j_int, j_double, j_string>(a, b, s));
    jc.execute();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_test___3Ljava_lang_Object_2(JNIEnv *env, jobject thiz,
                                                                        jobjectArray a) {

    jclass jcls = env->FindClass("java/lang/Object");
    jobjectArray jarr = env->NewObjectArray(1, jcls, NULL);
    jclass jicls = env->FindClass("java/lang/Integer");
    jmethodID jim = env->GetMethodID(jicls, "<init>", "(I)V");
    jobject jiobj = env->NewObject(jicls, jim, 10);

    env->SetObjectArrayElement(jarr, 0, jiobj);
    LOGV("sl2577 test success");

}