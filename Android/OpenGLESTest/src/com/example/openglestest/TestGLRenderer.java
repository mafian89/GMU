package com.example.openglestest;

import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.example.utils.FileUtils;
import com.example.utils.RawResourceReader;
import com.example.utils.ShaderHelper;
import com.example.utils.TextureHelper;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.graphics.Point;
import static android.opengl.GLES20.*;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import android.util.Log;
import android.view.Display;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.TextView;

//import com.example.openglestest.FPSCounter;

public class TestGLRenderer implements GLSurfaceView.Renderer {

	private Double sum = 0.0;
	private long count = 0;
	
	//public FPSCounter counterFPS;
	long startTime = System.nanoTime();
    int frames = 0;

    public void logFrame() {
        frames++;
        if(System.nanoTime() - startTime >= 1000000000) {
            Log.d("FPSCounter", "fps: " + frames);
            frames = 0;
            startTime = System.nanoTime();
        }
    }
	
	private final Context mActivityContext;
	//Context will be probably used for loading resources
	public TestGLRenderer(final Context activityContext) {
		mActivityContext = activityContext;	
	}
	
	@Override
	public void onDrawFrame(GL10 arg0) {
		Long startTime = System.currentTimeMillis();
		rendererNativeWrapper.on_draw_frame();
		Long estimatedTime = System.currentTimeMillis() - startTime;
		//Log.d("Draw", estimatedTime.toString());
		
		logFrame();
		
		/*count++;
		sum += estimatedTime;
		if (count == 100) {
			count = 0;
			sum /= 100.0;
			Log.d("Draw", sum.toString());
			sum = 0.0;
		}*/
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		rendererNativeWrapper.on_surface_changed(width, height);
	}

	/**
	 * Called every time new surface is created 
	 */
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		LoadedImgResult i1 = getByteArrayFromResource(R.drawable.texture);
		LoadedImgResult i2 = getByteArrayFromResource(R.drawable.floor);
		
		WindowManager wm = (WindowManager) mActivityContext.getSystemService(Context.WINDOW_SERVICE);
		Display display = wm.getDefaultDisplay();
		Point size = new Point();
		display.getSize(size);
		
		FileUtils.myNative(mActivityContext.getAssets());
		rendererNativeWrapper.injectTextures(i1.data, i2.data,i1.width,i1.height, i2.width, i2.height);
		rendererNativeWrapper.on_surface_created(size.x,size.y);
	}

	
	private LoadedImgResult getByteArrayFromResource(final int resourceId) {
		LoadedImgResult res = new LoadedImgResult();
		final BitmapFactory.Options options = new BitmapFactory.Options();
		options.inScaled = false;
		options.inPreferredConfig = Config.ARGB_8888;
		final Bitmap bitmap1 = BitmapFactory.decodeResource(mActivityContext.getResources(), resourceId, options);
		res.width = bitmap1.getWidth();
		res.height = bitmap1.getHeight();
		
		int bytes = bitmap1.getByteCount();
		ByteBuffer buffer = ByteBuffer.allocate(bytes); //Create a new buffer
		bitmap1.copyPixelsToBuffer(buffer); //Move the byte data to the buffer
		res.data = buffer.array(); //Get the underlying array containing the data.
		
		bitmap1.recycle();
		return res;
	}
	
	private class LoadedImgResult {
		//I don't want to use getters and setters...
		public byte[] data;
		public int width;
		public int height;
		
		public LoadedImgResult() {
			
		}
	}
}
