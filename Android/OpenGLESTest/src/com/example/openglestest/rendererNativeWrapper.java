package com.example.openglestest;

public class rendererNativeWrapper {
	static {
        System.loadLibrary("testNativeRenderer");
    }
 
    public static native void on_surface_created();
 
    public static native void on_surface_changed(int width, int height);
 
    public static native void on_draw_frame();
    
    public static native void injectTextures(int tex1, int tex2);
}
