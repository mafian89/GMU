package com.example.openglestest;

public class rendererNativeWrapper {
	static {
        System.loadLibrary("testNativeRenderer");
    }
 
    public static native void on_surface_created(int resx, int resy);
 
    public static native void on_surface_changed(int width, int height);
 
    public static native void on_draw_frame();
    
    public static native void injectTextures(byte [] tex1, byte [] tex2, int w1, int h1, int w2, int h2);
    
    public static native void switchEffect(int effectId);
    
    public static native void compileShaders();
}
