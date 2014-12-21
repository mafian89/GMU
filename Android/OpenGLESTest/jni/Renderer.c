/*
 * Renderer.cpp
 *
 *  Created on: 20.12.2014
 *      Author: Tomas
 */

#include "Renderer.h"
#include "logic.h"

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
  (JNIEnv * env, jclass clazz, jint tex1, jint tex2) {

}
