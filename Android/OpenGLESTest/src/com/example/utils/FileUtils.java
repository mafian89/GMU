package com.example.utils;

import android.content.res.AssetManager;

public class FileUtils {
	static {
        System.loadLibrary("testNativeRenderer");
    }
	public static native void myNative(AssetManager as);
}
