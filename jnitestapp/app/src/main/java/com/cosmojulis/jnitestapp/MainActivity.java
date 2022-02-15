package com.cosmojulis.jnitestapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.widget.TextView;

import com.cosmojulis.jnitestapp.databinding.ActivityMainBinding;
import com.cosmojulis.meta.JniHelper;
import com.cosmojulis.meta.JniInterface;

import java.io.Console;
import java.lang.reflect.Array;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'jnitestapp' library on application startup.
    static {
        System.loadLibrary("jnitestapp");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());


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

}