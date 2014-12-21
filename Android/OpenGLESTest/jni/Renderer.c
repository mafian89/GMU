/*
 * Renderer.cpp
 *
 *  Created on: 20.12.2014
 *      Author: Tomas
 */

#include "Renderer.h"
#include "logic.h"

//extern GLuint texID1,texID2;

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1surface_1created
    (JNIEnv * env, jclass cls) {
    on_surface_created();
}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1surface_1changed
    (JNIEnv * env, jclass cls, jint width, jint height) {
    on_surface_changed();
}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1draw_1frame
    (JNIEnv * env, jclass cls) {
    on_draw_frame();
}

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_injectTextures
  (JNIEnv * env, jclass clazz, jbyteArray tex1, jbyteArray tex2) {

	   jbyte*            jimgData = 0;
	   jboolean          isCopy = 0;
	   //jbyte*      (*GetByteArrayElements)(JNIEnv*, jbyteArray, jboolean*);
	   jimgData = (*env)->GetByteArrayElements( env, tex1, &isCopy );

	   glGenTextures(1, &texID1);

		glBindTexture(GL_TEXTURE_2D, texID1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, jimgData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

	   (*env)->ReleaseByteArrayElements( env, tex1, jimgData, JNI_ABORT );
}
