package com.example.openglestest;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

public class GLActivity extends Activity {

	//Surface view for drawing
	private GLSurfaceView mGLSurfaceView;
	private boolean rendererSet;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		//Create new surface view
		mGLSurfaceView = new GLSurfaceView(this);
		
		// Check if the system supports OpenGL ES 2.0.
		final ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
		final ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
		final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000;
		//mGLSurfaceView.setPreserveEGLContextOnPause(true);
		
		if(supportsEs2) {
			// Request an OpenGL ES 2.0 compatible context.
			mGLSurfaceView.setEGLContextClientVersion(2);

			// Set the renderer
			mGLSurfaceView.setRenderer(new TestGLRenderer(this));
			rendererSet = true;
		} else {
			//Only OpenGL ES 2.0 and higher is supported
			return;
		}
		
		//And draw into it
		setContentView(mGLSurfaceView);
	}
	
	@Override
	protected void onResume() 
	{
		// The activity must call the GL surface view's onResume() on activity onResume().
		super.onResume();
		if (rendererSet) {
			mGLSurfaceView.onResume();
		}
	}

	@Override
	protected void onPause() 
	{
		// The activity must call the GL surface view's onPause() on activity onPause().
		super.onPause();
		if (rendererSet) {
			mGLSurfaceView.onPause();
		}
	}
	
}
