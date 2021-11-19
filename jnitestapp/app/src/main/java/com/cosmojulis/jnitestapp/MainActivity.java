package com.cosmojulis.jnitestapp;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;

import android.app.Notification;
import android.os.Bundle;
import android.widget.TextView;

import com.cosmojulis.jnitestapp.databinding.ActivityMainBinding;

import java.lang.reflect.ParameterizedType;
import java.util.concurrent.Callable;
import java.util.function.Consumer;
import java.util.function.Function;

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

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
    }





    public native String stringFromJNI();

//    public interface Callback {
//        public void callbackInt(int a);
//    }
//
//    public Callback testCb() {
//        return new Callback() {
//            @Override
//            public void callbackInt(int a) {
//
//            }
//        };
//    }

//    public void testCbInt(Callback callback) {
//        callback.callbackInt(2577);
//    }

    public static void test() {
        System.out.println("sl2577 test void");
    }

    public static void test(int a) {
        System.out.println("sl2577 test " + a);
    }

    public static void test(int a, int b) {
        System.out.println("sl2577 test " + a + " " + b);
    }

    public static int testr(int a) {
        int r = a * 2;
        System.out.println("sl2577 testr a: " + a + ", ret = " + (a * 2));
        return r;
    }

    public static String test_combine(String a, String b) {
        String ab = a + b;
        System.out.println("sl2577 combine " + ab);
        return ab;
    }

    public static void teststr(String a) {
        System.out.println("sl2577 str " + a);
    }

    public static void test_interface_object(MyCallback c) {
        c.callback();
    }
}