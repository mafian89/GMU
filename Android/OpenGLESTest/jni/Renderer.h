#include <jni.h>
/* Header for class com_example_openglestest_rendererNativeWrapper */

#ifndef RENDERER_H_
#define RENDERER_H_
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_openglestest_rendererNativeWrapper
 * Method:    on_surface_created
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1surface_1created
  (JNIEnv *, jclass);

/*
 * Class:     com_example_openglestest_rendererNativeWrapper
 * Method:    on_surface_changed
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1surface_1changed
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_example_openglestest_rendererNativeWrapper
 * Method:    on_draw_frame
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_on_1draw_1frame
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_example_openglestest_rendererNativeWrapper_injectTextures
  (JNIEnv *, jclass, jbyteArray, jbyteArray);

#ifdef __cplusplus
}
#endif
#endif
