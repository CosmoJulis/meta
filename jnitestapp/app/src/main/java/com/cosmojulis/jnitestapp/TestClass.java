package com.cosmojulis.jnitestapp;

import com.cosmojulis.meta.JniHelper;

public class TestClass {
    public void javaMethod(int i, JniHelper jhi) {
        System.out.println("i = " + i);
        jhi.callback(5, "hello world");
    }
}
