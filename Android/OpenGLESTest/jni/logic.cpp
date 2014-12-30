/*
 * logic.cpp
 *
 *  Created on: 20.12.2014
 *      Author: Tomas
 */

#include "logic.h"
#include "FileUtils.h"
#include "ShadersUtils.h"

//static GLSLShader basicShader;
GLuint program;
GLuint pos_loc, uv_loc, tex1_loc, tex2_loc;

SHADER_PARAMS shaderParams[NUM_OF_SHADERS];
//Hardcoded - IMPORTANT!!
float arr[2*1920*1080];

int actualProgram = 0;
int areShadersLoaded = 0;

#define EPRINTF(...)  __android_log_print(ANDROID_LOG_ERROR,"logic",__VA_ARGS__)
#define DPRINTF(...)  __android_log_print(ANDROID_LOG_DEBUG,"logic",__VA_ARGS__)

GLuint VBO;
GLuint HistogramVBO;
GLuint FBO;
//Quad verticles - omitted z coord, because it will always be 1
const float pos[] = {
		-1.0, 1.0,
		1.0, 1.0,
		-1.0, -1.0,
		1.0, -1.0
};

const float uv[] = {
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0
};

void initQuad() {
	//Generate VBO
	glGenBuffers(1, &VBO);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Alocate buffer
	glBufferData(GL_ARRAY_BUFFER, 16*sizeof(float), 0, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Fill VBO
	glBufferSubData(GL_ARRAY_BUFFER, 0, 8*sizeof(float), pos);
	glBufferSubData(GL_ARRAY_BUFFER, 8 * sizeof(float), 8*sizeof(float), uv);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawQuad() {
	//int actualProgram = 0;
	glUseProgram(shaderParams[actualProgram].prog);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(shaderParams[actualProgram].pos_loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
	glVertexAttribPointer(shaderParams[actualProgram].uv_loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (GLvoid*)(sizeof(float)* 8));
	glEnableVertexAttribArray(shaderParams[actualProgram].pos_loc);
	glEnableVertexAttribArray(shaderParams[actualProgram].uv_loc);

	glUniform1i(shaderParams[actualProgram].tex1_loc, 0);
	glUniform1i(shaderParams[actualProgram].tex2_loc, 1);

	/*glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texID2);*/

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void on_surface_created() {
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	//DPRINTF("%d",shaderParams[actualProgram].prog);
	changeEffect(actualProgram);
}

void on_surface_changed() {
    // No-op
}

void on_draw_frame() {
	glClear(GL_COLOR_BUFFER_BIT);
	//Disable depth test
	glDisable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID1);

	//computeHistogram();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID1);

	//TEMP CHANGE
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texID2);

	drawQuad();

	glFinish();
}

void computeHistogram() {
	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);
	//Additive
	glBlendEquation(GL_FUNC_ADD);
	glUseProgram(shaderParams[actualProgram].prog);

	glBindBuffer(GL_ARRAY_BUFFER, HistogramVBO);

	glVertexAttribPointer(shaderParams[actualProgram].pos_loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(shaderParams[actualProgram].pos_loc);

	glUniform1i(shaderParams[actualProgram].tex1_loc, 0);
	glUniform1i(shaderParams[actualProgram].tex2_loc, 1);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	//Compute histogram
	glDrawArrays(GL_POINTS, 0, textureWidth*textureHeight);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	//Disable blending
	glDisable(GL_BLEND);

	/*int hPixels[256*3];
	glReadPixels(0, 0, 256, 1, GL_RGB, GL_UNSIGNED_BYTE, hPixels);
	for(int j = 0; j < 256*3; j++) {
		if((j % 3) == 0)
			DPRINTF("%d",hPixels[j]);
	}*/

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void changeEffect(int i) {
	DPRINTF("Changing effect to: %s [%d]", effectsShaders[i][1],i);
	actualProgram = i;
	//compileAndSetTargetedShader(actualProgram);
}


void compileAllShaders() {
	if(areShadersLoaded == 0) {
		initQuad();
		DPRINTF("About to compile all shaders");
		for(int i=0; i < NUM_OF_SHADERS; i++) {
			DPRINTF("%s %s [%d]", effectsShaders[i][0],effectsShaders[i][1],i);
			compileAndSetTargetedShader(i);
		}
		areShadersLoaded = 1;
	}
}

void compileAndSetTargetedShader(int i) {
	shaderParams[i].prog = build_program_from_assets(effectsShaders[i][0], effectsShaders[i][1]);
	shaderParams[i].pos_loc = glGetAttribLocation(shaderParams[i].prog, "vPosition");
	shaderParams[i].uv_loc = glGetAttribLocation(shaderParams[i].prog, "vUV");
	shaderParams[i].tex1_loc = glGetUniformLocation(shaderParams[i].prog, "tex");
	shaderParams[i].tex2_loc = glGetUniformLocation(shaderParams[i].prog, "tex2");
	//DPRINTF("%s %s", effectsShaders[i][0], effectsShaders[i][1]);
}

void initFBO() {
	initRenderTex();

	glGenFramebuffers (1, &FBO);
	glBindFramebuffer (GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, histogramTex, 0);


	DPRINTF("Checking framebuffer status...");
	bool ok = true;
	// check FBO status
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	switch(status)
	{
	case GL_FRAMEBUFFER_COMPLETE:
		DPRINTF("Framebuffer complete.");
		break ;

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		EPRINTF("Framebuffer incomplete: Attachment is NOT complete.");
		ok = false;
		break ;

	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		EPRINTF("Framebuffer incomplete: No image is attached to FBO.");
		ok = false;
		break ;

	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
		EPRINTF("Framebuffer incomplete: Attached images have different dimensions.");
		ok = false;
		break ;

	case GL_FRAMEBUFFER_UNSUPPORTED:
		EPRINTF("Unsupported by FBO implementation.");
		ok = false;
		break ;

	default:
		EPRINTF("Unknown error.");
		ok = false;
		break ;
	}

	glBindFramebuffer (GL_FRAMEBUFFER, 0);

	if(!ok) {
		return;
	}

}
//GL_HALF_FLOAT_OES
void initRenderTex() {
	glGenTextures (1, &histogramTex);
	glBindTexture (GL_TEXTURE_2D, histogramTex);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA , 256, 1, 0, GL_RGBA, GL_HALF_FLOAT_OES, 0);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void initPointVBO(int w, int h) {
	DPRINTF("In point VBO initialization w was: %d and h was: %d",w,h);

	for(int i=0;i<w*h;i++) {
		arr[2*i] = i % w;
		arr[2*i+1] = (float)((int)(i / w));
	}


	//Generate VBO
	glGenBuffers(1, &HistogramVBO);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, HistogramVBO);

	//Alocate buffer
	glBufferData(GL_ARRAY_BUFFER, 2*w*h*sizeof(float), arr, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Fill VBO
	//glBufferSubData(GL_ARRAY_BUFFER, 0, 2*w*h*sizeof(float), arr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	/*for(int k=0; k < 16; k++) {
		DPRINTF("k:%d - %f %f",k,arr[2*k],arr[2*k + 1]);
	}*/
}


