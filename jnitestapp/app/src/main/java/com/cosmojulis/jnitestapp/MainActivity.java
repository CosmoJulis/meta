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

    public static String getSignature(Method m){
        String sig;
        try {
            Field gSig = Method.class.getDeclaredField("signature");
            gSig.setAccessible(true);
            sig = (String) gSig.get(m);
            if(sig!=null) return sig;
        } catch (IllegalAccessException | NoSuchFieldException e) {
//            e.printStackTrace();
        }

        StringBuilder sb = new StringBuilder("(");
        for(Class<?> c : m.getParameterTypes())
            sb.append((sig=Array.newInstance(c, 0).toString())
                    .substring(1, sig.indexOf('@')));
        return sb.append(')')
                .append(
                        m.getReturnType()==void.class?"V":
                                (sig=Array.newInstance(m.getReturnType(), 0).toString()).substring(1, sig.indexOf('@'))
                )
                .toString();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());



        new Handler().postDelayed(() -> {

            ArrayList<Object> arr = new ArrayList<Object>();
            arr.add("hello");
            arr.add(2);
            my_test(arr.toArray());

            //            test(arr.toArray());

            test(5, 0.5, "hello world", new JniInterface() {
                @Override
                public <T> void callback(T... arr) {
                    for (Object i: arr) {
                        System.out.println("sl2577 " + i);
                    }
                }
            });

        }, 2000);
    }

    public <T> void my_test(T... arr) {
        System.out.println(arr.getClass().toString());
        for (Object i: arr) {
            System.out.println("sl2577 " + i);
        }
    }

    public native String stringFromJNI();

    public native void test();
    public native void test(Object a[]);
    public native void testClassTest();

    public native void test(int a, double b, String s, JniInterface jhi);

    public static void javaMethod(int i, JniHelper jhi) {
        System.out.println("i = " + i);
        jhi.callback(5, "hello world");
    }
}