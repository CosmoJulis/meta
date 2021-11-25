package com.cosmojulis.meta;

//public final class JniHelper {
//    private JniHelper () { }

public class JniHelper {
    // a is Serializable
    public native <T> void callback(T...a);

//    public <T> void hello(T ... a) {
//        System.out.println("sl2577 hello array");
//        callback(a);
//    }



}
