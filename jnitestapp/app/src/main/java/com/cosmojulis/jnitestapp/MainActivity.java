package com.cosmojulis.jnitestapp;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;

import android.app.Notification;
import android.os.Bundle;
import android.os.Handler;
import android.widget.TextView;

import com.cosmojulis.jnitestapp.databinding.ActivityMainBinding;
import com.cosmojulis.meta.JniHelperInterface;

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

        new Handler().postDelayed(() -> {
//            JniHelperInterface jhi = new JniHelperInterface();
//            jhi.callback();
            test();
        }, 3000);
    }

    public native String stringFromJNI();

    public native void test();


    public static void callback(JniHelperInterface jhi) {
        jhi.callback();
    }


}