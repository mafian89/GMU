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
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import static android.opengl.GLES20.*;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import android.util.Log;

public class TestGLRenderer implements GLSurfaceView.Renderer {

	private final Context mActivityContext;
	
	private class ResTmp {
		public float x;
		public float y;
		
		public ResTmp(float x, float y) {
			this.x = x;
			this.y = y;
		}
		
		@Override
		public String toString() {
			return "x: " + this.x + " y: " + this.y;
		}
	}
	//Context will be probably used for loading resources
	public TestGLRenderer(final Context activityContext) {
		mActivityContext = activityContext;
		int kernelSize = 5;

		
		ResTmp[] uv_offset = new ResTmp[kernelSize*kernelSize];
		float xInc = 1.0f / 800.0f;
		float yInc = 1.0f /600.0f;

		//plnime offset
		for (int i = 0; i < (kernelSize-1); i++) 
		{
			for (int j = 0; j < (kernelSize-1); j++) 
			{
				uv_offset[((i*kernelSize)+j)] = new ResTmp( (float)((-1.0 * xInc) + (float)((i) * xInc)) , (float)((-1.0 * yInc)+(float)((j) * yInc)) );//vec2(  , ((-1.0 * yInc)+(float(j) * yInc)) );
			}

		}
		
		for(int k = 0; k < kernelSize*kernelSize; k++) {
			//Log.d("OFFSET", uv_offset[k].toString());
		}
		
		
	}
	
	@Override
	public void onDrawFrame(GL10 arg0) {
		rendererNativeWrapper.on_draw_frame();
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
		
		FileUtils.myNative(mActivityContext.getAssets());
		rendererNativeWrapper.on_surface_created();
		rendererNativeWrapper.injectTextures(i1.data, i2.data,i1.width,i1.height, i2.width, i2.height);
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
