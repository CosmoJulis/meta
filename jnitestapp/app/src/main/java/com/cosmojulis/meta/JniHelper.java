package com.cosmojulis.meta;

//public final class JniHelper {
//    private JniHelper () { }

import java.util.ArrayList;

public class JniHelper {
    // a is Serializable
    public native <T> void callback(T...a);
}
