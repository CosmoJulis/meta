package com.cosmojulis.meta;

public class JniHelperInterface {
    static {
        System.loadLibrary("jnitestapp");
    }

    public native void callback();
//    {
//        System.out.println("sl2577 JniHelperInterface void callback()");
//    }
}
