/*
 * Renderer.cpp
 *
 *  Created on: 20.12.2014
 *      Author: Tomas
 */

#include "Renderer.h"
#include "logic.h"
#include <time.h>

//extern GLuint texID1,texID2;
#define DPRINTF(...)  __android_log_print(ANDROID_LOG_DEBUG,"Renderer",__VA_ARGS__)

/* return current time in milliseconds */
static double now_ms(void) {

    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;

}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1surface_1created(
		JNIEnv * env, jclass cls, jint resx, jint resy) {

	DPRINTF("Display resolution: %d x %d",resx,resy);
	displayWidth = resx;
	displayHeight = resy;
	//initPointVBO(textureWidth,textureHeight);
	initFBO();
	compileAllShaders();
	DPRINTF("compileAllShaders() done");
	on_surface_created();
}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1surface_1changed(
		JNIEnv * env, jclass cls, jint width, jint height) {
	on_surface_changed();
}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1draw_1frame(
		JNIEnv * env, jclass cls) {
	double start = now_ms(); // start time
	on_draw_frame();
	double end = now_ms(); // finish time

	double delta = end - start; // time your code took to exec in ms
	//DPRINTF("DRAW TIME: %f",delta);
}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_injectTextures(
		JNIEnv * env, jclass clazz, jbyteArray tex1, jbyteArray tex2,jint w1,jint h1,jint w2,jint h2) {

	DPRINTF("width: %d and height: %d",w1,h1);
	textureWidth = w1;
	textureHeight = h1;
	jbyte* jimgData = 0;
	jboolean isCopy = 0;
	jimgData = (*env)->GetByteArrayElements(env, tex1, &isCopy);
	generateTexture(&texID1,jimgData,w1,h1);
	(*env)->ReleaseByteArrayElements(env, tex1, jimgData, JNI_ABORT);


	jbyte* jimgData1 = 0;
	jboolean isCopy1 = 0;
	jimgData1 = (*env)->GetByteArrayElements(env, tex2, &isCopy1);
	generateTexture(&texID2,jimgData1,w2,h2);
	(*env)->ReleaseByteArrayElements(env, tex2, jimgData1, JNI_ABORT);

}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_switchEffect
  (JNIEnv * env, jclass clazz, jint effectId) {
	changeEffect(effectId);
}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_compileShaders
  (JNIEnv * env, jclass clazz) {
	compileAllShaders();
}

void generateTexture(GLuint *id, jbyte * data, int w, int h) {
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	//Texture filtering should be set to GL_NEAREST in case if we want to compute histogram
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);


}
