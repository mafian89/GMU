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

//#define EPRINTF(...)  __android_log_print(ANDROID_LOG_ERROR,"logic",__VA_ARGS__)
#define DPRINTF(...)  __android_log_print(ANDROID_LOG_DEBUG,"logic",__VA_ARGS__)

GLuint VBO;
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
	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(pos_loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
	glVertexAttribPointer(uv_loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (GLvoid*)(sizeof(float)* 8));
	glEnableVertexAttribArray(pos_loc);
	glEnableVertexAttribArray(uv_loc);

	glUniform1i(tex1_loc, 0);
	glUniform1i(tex2_loc, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texID2);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void on_surface_created() {

	program = build_program_from_assets("Shaders/basic.vs", "Shaders/threshold.frag");
	pos_loc = glGetAttribLocation(program, "vPosition");
	uv_loc = glGetAttribLocation(program, "vUV");
	tex1_loc = glGetUniformLocation(program, "tex");
	tex2_loc = glGetUniformLocation(program, "tex2");

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    initQuad();
}

void on_surface_changed() {
    // No-op
}

void on_draw_frame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawQuad();
}

void changeEffect(int i) {
	DPRINTF("Changing effect to: %d", i);
	//program = build_program_from_assets("Shaders/basic.vs", "Shaders/basic.frag");
}




