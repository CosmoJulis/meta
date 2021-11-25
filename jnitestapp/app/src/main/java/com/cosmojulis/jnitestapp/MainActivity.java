package com.cosmojulis.jnitestapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.widget.TextView;

import com.cosmojulis.jnitestapp.databinding.ActivityMainBinding;
import com.cosmojulis.meta.JniHelper;

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



        new Handler().postDelayed(() -> {
            test();
            test();

        }, 3000);
    }

    public native String stringFromJNI();

    public native void test();

    public static void javaMethod(JniHelper jhi) {
//        jhi.callback(1, 2, "string");
//        jhi.callback();
//        jhi.hello(1, 2, 3);
//        jhi.hello();
//        jniHelperClass.getMethod("hello").invoke(null);
    }

}