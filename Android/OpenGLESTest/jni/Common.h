/*
 * Common.h
 *
 *  Created on: 20.12.2014
 *      Author: Tomas
 */

#ifndef COMMON_H_
#define COMMON_H_


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

typedef struct {
	const long data_length;
	const void* data;
	const void* file_handle;
} FileData;
/*
void on_surface_created() {
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

void on_surface_changed() {
    // No-op
}

void on_draw_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
}*/


#endif /* COMMON_H_ */
