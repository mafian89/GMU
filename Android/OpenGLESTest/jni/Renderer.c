/*
 * Renderer.cpp
 *
 *  Created on: 20.12.2014
 *      Author: Tomas
 */

#include "Renderer.h"
#include "logic.h"

//extern GLuint texID1,texID2;

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1surface_1created(
		JNIEnv * env, jclass cls) {
	on_surface_created();
}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1surface_1changed(
		JNIEnv * env, jclass cls, jint width, jint height) {
	on_surface_changed();
}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1draw_1frame(
		JNIEnv * env, jclass cls) {
	on_draw_frame();
}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_injectTextures(
		JNIEnv * env, jclass clazz, jbyteArray tex1, jbyteArray tex2,jint w1,jint h1,jint w2,jint h2) {

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

void generateTexture(GLuint *id, jbyte * data, int w, int h) {
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}
