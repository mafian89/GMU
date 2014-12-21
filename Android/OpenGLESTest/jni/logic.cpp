/*
 * logic.cpp
 *
 *  Created on: 20.12.2014
 *      Author: Tomas
 */

#include "logic.h"
#include "FileUtils.h"
#include "ShadersUtils.h"

static GLSLShader basicShader;

//#define EPRINTF(...)  __android_log_print(ANDROID_LOG_ERROR,"logic",__VA_ARGS__)
//#define DPRINTF(...)  __android_log_print(ANDROID_LOG_DEBUG,"logic",__VA_ARGS__)

void on_surface_created() {
	const FileData vertex_shader_source = get_asset_data("Shaders/texture_viewer_vertex.glsl");
	const FileData fragment_shader_source = get_asset_data("Shaders/texture_viewer_fragment.glsl");

	//__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "Need to print : %d",vertex_shader_source.data_length);

	const char * vertex = (const char *) vertex_shader_source.data;
	const char * fragment = (const char *) fragment_shader_source.data;
	basicShader.LoadFromString(GL_VERTEX_SHADER, vertex);
	basicShader.LoadFromString(GL_FRAGMENT_SHADER, fragment);
	basicShader.CreateAndLinkProgram();

	//__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "Need to print : %s",vertex);

	//Clean-up
	release_asset_data(&vertex_shader_source);
	release_asset_data(&fragment_shader_source);
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

void on_surface_changed() {
    // No-op
}

void on_draw_frame() {
    glClear(GL_COLOR_BUFFER_BIT);
}



