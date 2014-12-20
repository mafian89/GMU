package com.example.openglestest;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.example.utils.RawResourceReader;
import com.example.utils.ShaderHelper;
import com.example.utils.TextureHelper;

import android.content.Context;
import static android.opengl.GLES20.*;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import android.util.Log;

public class TestGLRenderer implements GLSurfaceView.Renderer {

	//private float[] mModelMatrix = new float[16];
	private float[] mProjMatrix = new float[16];
	//private float[] mViewMatrix = new float[16];
	//private float[] mMVPMatrix = new float[16];
	
	private final FloatBuffer mPositions;
	private final FloatBuffer mTextureCoords;
	
	private final Context mActivityContext;
	
	/** How many bytes per float. */
	private final int mBytesPerFloat = 4;	
	/** Size of the position data in elements. */
	private final int mPositionDataSize = 2;
	private final int mTextureCoordsDataSize = 2;
	
	
	private int mTextureProgramHandle;
	private int mPositionHandle;
	private int mTextureCoordsHandle;
	private int mTexture1UniformHandle;
	private int mTexture2UniformHandle;
	private int mTexture1DataHandle;
	private int mTexture2DataHandle;
	
	//Context will be probably used for loading resources
	public TestGLRenderer(final Context activityContext) {
		mActivityContext = activityContext;
		/*
		 * 1   4
		 * +---+
		 * |\  |
		 * | \ |
		 * |  \|
		 * +---+
		 * 3   2
		 * Z coordinate omitted
		 */
		final float[] positionData = {
			-1.f,1.f, 	//1
			1.f,-1.f, 	//2
			-1.f,-1.f,	//3
			
			1.f,-1.f, 	//3
			-1.f,1.f,	//1	
			1.f,1.f		//4
		};
		
		/*
		 *(0,1)  (1,1) 
		 *  +------+
		 *  |      |
		 *  |      |
		 *  +------+
		 *(0,0)  (1,0)
		 *
		 * v
		 * ^
		 * |
		 * +---> u
		 */
		final float[] textureCoordData = {
			0.f, 1.f,
			1.f,0.f,
			0.f,0.f,
			
			1.f,0.f,
			0.f, 1.f,
			1.f,1.f
		};
		
		//Init buffers
		mPositions = ByteBuffer.allocateDirect(positionData.length * mBytesPerFloat)
		        .order(ByteOrder.nativeOrder()).asFloatBuffer();							
		mPositions.put(positionData).position(0);
		
		mTextureCoords = ByteBuffer.allocateDirect(textureCoordData.length * mBytesPerFloat)
		        .order(ByteOrder.nativeOrder()).asFloatBuffer();							
		mTextureCoords.put(textureCoordData).position(0);
	}
	
	@Override
	public void onDrawFrame(GL10 arg0) {
		// TODO Auto-generated method stub
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(mTextureProgramHandle);   
		
		drawQuad();
		
		glUseProgram(0);
		
	}
	
	private void drawQuad() {
		mPositions.position(0);		
        glVertexAttribPointer(mPositionHandle, mPositionDataSize, GL_FLOAT, false,
        		0, mPositions);        
        glEnableVertexAttribArray(mPositionHandle);  
        
        mTextureCoords.position(0);		
        glVertexAttribPointer(mTextureCoordsHandle, mTextureCoordsDataSize, GL_FLOAT, false,
        		0, mTextureCoords);        
        glEnableVertexAttribArray(mTextureCoordsHandle);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTexture1DataHandle);
        glUniform1i(mTexture1UniformHandle, 0); 
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mTexture2DataHandle);
        glUniform1i(mTexture2UniformHandle, 1); 
        
        glDrawArrays(GL_TRIANGLES, 0, 6);    
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		// TODO Auto-generated method stub
		glViewport(0, 0, width, height);

	    float ratio = (float) width / height;

	    // create a projection matrix from device screen geometry
	    Matrix.frustumM(mProjMatrix, 0, -ratio, ratio, -1, 1, 1, 10);
	}

	/**
	 * Called every time new surface is created 
	 */
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		// TODO Auto-generated method stub
		// Set the background clear color to black.
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
				
		// Use culling to remove back faces.
		//glEnable(GL_CULL_FACE);
				
		// Enable depth testing
		glEnable(GL_DEPTH_TEST);
		
		String textureVS = RawResourceReader.readTextFileFromRawResource(mActivityContext, R.raw.texture_viewer_vertex);
		String textureFS = RawResourceReader.readTextFileFromRawResource(mActivityContext, R.raw.texture_viewer_fragment);
		
		final int pointVertexShaderHandle = ShaderHelper.compileShader(GL_VERTEX_SHADER, textureVS);
        final int pointFragmentShaderHandle = ShaderHelper.compileShader(GL_FRAGMENT_SHADER, textureFS);
        mTextureProgramHandle = ShaderHelper.createAndLinkProgram(pointVertexShaderHandle, pointFragmentShaderHandle, 
        		new String[] {"vPosition","vUV","tex","tex2"}); 
        
        //Get uniforms, attributes ...
        glUseProgram(mTextureProgramHandle);
		
		mPositionHandle = glGetAttribLocation(mTextureProgramHandle,"vPosition");
		mTextureCoordsHandle = glGetAttribLocation(mTextureProgramHandle,"vUV");
		mTexture1UniformHandle = glGetUniformLocation(mTextureProgramHandle, "tex");
		mTexture2UniformHandle = glGetUniformLocation(mTextureProgramHandle, "tex2");
		//glUniform1i(mTextureUniformHandle, 0);    
		
		mTexture1DataHandle = TextureHelper.loadTexture(mActivityContext, R.drawable.floor);
		mTexture2DataHandle = TextureHelper.loadTexture(mActivityContext, R.drawable.texture);
		
		glUseProgram(0);
		
	}

}
