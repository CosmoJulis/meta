# JNI Helper 


## Callback from C++ to Java 

use class JniHelper to callback values.

### Static Method 

```` Java
public static void javaStaticMethod(int i, JniHelper jni) {
    System.out.println("javaStaticMethod");
    jni.callback(5, "hello world");
}
````

```` C++
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
````

### Object Method

```` Java
// in TestClass
public void javaMethod(int i, JniHelper jni) {
    System.out.println("javaMethod");
    jni.callback(5, "hello world");
}
````

```` C++
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
}````

## Callback from Java to C++

use class JniInteface to callback value

```` Java
protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    javaMethod(5, new JniInterface() {
        @Override
        public <T> void callback(T... arr) {
            for (Object i: arr) {
                System.out.println(i);
            }
        }
    });
}

public native void javaMethod(int i, JniInterface jhi);
````

```` C++
extern "C"
JNIEXPORT void JNICALL
Java_com_cosmojulis_jnitestapp_MainActivity_testFromJavaToCppCall(JNIEnv *env, 
                                                                  jobject thiz, 
                                                                  jint a,
                                                                  jobject jni) {

    auto jc = j_call<j_void, j_array<j_int, j_string>>(jni, "callback",
                                                       make_array<j_int, j_string>(a, "hello world"));
    jc.execute();
}

````



```` Java

// MainActivity.java

protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    new Handler().postDelayed(() -> {
        testFromCppToJavaStaticCall();
        testFromCppToJavaCall(this);
        testFromJavaToCppCall();
    }, 2000);
}

public native void testFromCppToJavaStaticCall();
public native void testFromCppToJavaCall(MainActivity m);

public static void javaStaticMethod(int i, JniHelper jni) {
    System.out.println("javaStaticMethod");
    jni.callback(5, "hello world");
}

public void javaMethod(int i, JniHelper jni) {
    System.out.println("javaMethod");
    jni.callback(5, "hello world");
}

public void testFromJavaToCppCall() {
    System.out.println("testFromJavaToCppCall");
    testFromJavaToCppCall(5, new JniInterface() {
        @Override
        public <T> void callback(T... arr) {
            System.out.println("testFromJavaToCppCall callback");
            for (Object i: arr) {
                System.out.println(i);
            }
        }
    });
}

public native void testFromJavaToCppCall(int a, JniInterface jni);

````


```` C++

// native-lib.cpp

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

````
