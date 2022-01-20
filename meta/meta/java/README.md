# JNI Helper 


## C++ to Java Callback

use class JniHelper to callback values.

### Static Method 

```` Java
public static void javaStaticMethod(int i, JniHelper jhi) {
    System.out.println("i = " + i);
    jhi.callback(5, "hello world");
}
````

```` C++
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
````

### Object Method

```` Java
// in TestClass
public void javeMethod(int i, JniHelper jhi) {
    System.out.println("i = " + i);
    jhi.callback(5, "hello world");
}
````

```` C++
auto jc = j_call<
            j_void, 
            j_int, 
            j_object>(
            j_base_object("com.cosmojulis.jnitestapp.TestClass"), 
            "javaMethod", 
            5, 
            j_helper<
                j_void, 
                j_int, 
                j_string>([](int i, std::string a){
                    LOGV("jnihelp callback %d, %s", i, a.c_str());
            }));
jc.execute();
````

## Java to C++ Callback

use class JniInteface to callback value




