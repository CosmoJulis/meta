package com.cosmojulis.meta;

public class JniHelper {
    // a is Serializable
    public native <T> void callback(T...a);
}
