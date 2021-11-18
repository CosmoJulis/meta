#include <jni.h>
#include <string>
#include "jni_helper.hpp"
#include <variant>

using namespace meta::jni::helper;

void test() {
    auto jc = j_call<j_void>("com.cosmojulis.jnitestapp.MainActivity", "test");
    jc.execute();
}

void test(int a) {
    auto jc = j_call<j_void, j_int>("com.cosmojulis.jnitestapp.MainActivity", "test", a);
    jc.execute();
}

void test(int a, int b) {
    auto jc = j_call<j_void, j_int, j_int>("com.cosmojulis.jnitestapp.MainActivity", "test", a, b);
    jc.execute();
}

int testr(int a) {
    auto jc = j_call<j_int, j_int>("com.cosmojulis.jnitestapp.MainActivity", "testr", a);
    int ret = int(jc.execute());
    return ret;
}

void testInterface() {

}

extern "C" JNIEXPORT jstring JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {


    test();
    test(5);
    test(5, 10);
    int r = testr(5);
    std::string hello = std::to_string(r);

    return env->NewStringUTF(hello.c_str());
}



