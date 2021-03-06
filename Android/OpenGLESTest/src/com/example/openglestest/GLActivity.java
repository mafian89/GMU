package com.example.openglestest;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.graphics.Color;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.EditText;
import android.widget.TextView;

public class GLActivity extends Activity {

	//Surface view for drawing
	private GLSurfaceView mGLSurfaceView;
	private boolean rendererSet;
	private TestGLRenderer renderer;
	private static TextView textView;
	
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
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		
		if(supportsEs2) {
			// Request an OpenGL ES 2.0 compatible context.
			mGLSurfaceView.setEGLContextClientVersion(2);
			renderer = new TestGLRenderer(this);
			// Set the renderer
			mGLSurfaceView.setRenderer(renderer);
			rendererSet = true;
			//rendererNativeWrapper.compileShaders();
		} else {
			//Only OpenGL ES 2.0 and higher is supported
			return;
		}
		
		//And draw into it
		setContentView(mGLSurfaceView);
		
		textView = new TextView(this);
		textView.setText("Input Image 1");
		//textView.setTextColor(Color.parseColor("#bdbdbd"));
		textView.setTextColor(Color.parseColor("#ff0508"));
		addContentView(textView, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
		//setContentView(R.layout.activity_gl);
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
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.basic) {
			rendererNativeWrapper.switchEffect(0);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.basic_mask) {
			rendererNativeWrapper.switchEffect(1);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.threshold) {
			rendererNativeWrapper.switchEffect(2);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.adaptive_threshold_mean) {
			rendererNativeWrapper.switchEffect(3);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.adaptive_threshold_meanC) {
			rendererNativeWrapper.switchEffect(4);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.adaptive_threshold_median) {
			rendererNativeWrapper.switchEffect(5);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.adaptive_threshold_minMax) {
			rendererNativeWrapper.switchEffect(6);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.bitwise_and) {
			rendererNativeWrapper.switchEffect(7);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.bitwise_or) {
			rendererNativeWrapper.switchEffect(8);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.bitwise_xor) {
			rendererNativeWrapper.switchEffect(9);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.bitwise_not) {
			rendererNativeWrapper.switchEffect(10);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.bitwise_nand) {
			rendererNativeWrapper.switchEffect(11);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.bitwise_nor) {
			rendererNativeWrapper.switchEffect(12);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.dilation) {
			rendererNativeWrapper.switchEffect(13);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.erosion) {
			rendererNativeWrapper.switchEffect(14);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.opening) {
			rendererNativeWrapper.switchEffect(15);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.closing) {
			rendererNativeWrapper.switchEffect(16);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.mean_filter) {
			rendererNativeWrapper.switchEffect(17);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.median_filter) {
			rendererNativeWrapper.switchEffect(18);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.gaussian_filter) {
			rendererNativeWrapper.switchEffect(19);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.gaussian_filter_sep) {
			rendererNativeWrapper.switchEffect(20);
			textView.setText(item.getTitle());
			return true;
		} else if (id == R.id.adaptive_threshold_meanC_textures) {
			rendererNativeWrapper.switchEffect(22);
			textView.setText(item.getTitle());
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

}
