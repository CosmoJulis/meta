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

    std::string hello = test_combine("foo", "bar");

    return env->NewStringUTF(hello.c_str());
}



