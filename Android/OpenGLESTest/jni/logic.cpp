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
#define DPRINTF(...)  __android_log_print(ANDROID_LOG_DEBUG,"logic",__VA_ARGS__)

GLuint VBO;

float pos[] = {
		-1.0, 1.0,
		1.0, 1.0,
		-1.0, -1.0,
		1.0, -1.0
};

float uv[] = {
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0
};

void initQuad() {

	basicShader.Use();
	//Create uniforms and attributes (filled later)
	basicShader.AddAttribute("vPosition");
	basicShader.AddAttribute("vUV");
	basicShader.AddUniform("tex1");
	basicShader.AddUniform("tex2");


	//Quad verticles - omitted z coord, because it will always be 1
	float pos[] = {
		-1.0, 1.0,
		1.0, 1.0,
		-1.0, -1.0,
		1.0, -1.0
	};

	float uv[] = {
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0
	};
	glUniform1i(basicShader("tex1"), 0);
	glUniform1i(basicShader("tex2"), 1);

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
	basicShader.UnUse();
}

void drawQuad() {

	basicShader.Use();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(basicShader["vPosition"], 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
	glVertexAttribPointer(basicShader["vUV"], 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (GLvoid*)(sizeof(float)* 8));
	glEnableVertexAttribArray(basicShader["vPosition"]);
	glEnableVertexAttribArray(basicShader["vUV"]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID1);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	basicShader.UnUse();


}

void on_surface_created() {
	const FileData vertex_shader_source = get_asset_data("Shaders/texture_viewer_vertex.glsl");
	const FileData fragment_shader_source = get_asset_data("Shaders/texture_viewer_fragment.glsl");

	//__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "Need to print : %d",vertex_shader_source.data_length);

	const char * vertex = (const char *) vertex_shader_source.data;
	const char * fragment = (const char *) fragment_shader_source.data;
	basicShader.LoadFromString(GL_VERTEX_SHADER, vertex, vertex_shader_source.data_length);
	basicShader.LoadFromString(GL_FRAGMENT_SHADER, fragment, fragment_shader_source.data_length);
	basicShader.CreateAndLinkProgram();

	//__android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "Need to print : %s",vertex);
	//DPRINTF("JSEM TU");
	//Clean-up
	release_asset_data(&vertex_shader_source);
	release_asset_data(&fragment_shader_source);
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    //DPRINTF("Pred init quad");
    initQuad();
}

void on_surface_changed() {
    // No-op
}

void on_draw_frame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawQuad();
}



