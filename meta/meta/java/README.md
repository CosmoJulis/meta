# JNI Helper 


## Callback from C++ to Java 

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

## Callback from Java to C++

use class JniInteface to callback value

```` Java
    javaMethod(5, new JniInterface() {
        @Override
        public <T> void callback(T... arr) {
            for (Object i: arr) {
                System.out.println(i);
            }
        }
    });
    
    public native void javaMethod(int i, JniInterface jhi);
````

```` C++
int a = 1;
double b = 0.5f;
auto jc = j_call<j_void, j_array<j_int, j_double>>(j_object(jhi), "callback",
                         make_array<j_int, j_double, j_string>(a, b));
jc.execute();
````


