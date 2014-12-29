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

int actualProgram = 0;
int areShadersLoaded = 0;

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
	glUseProgram(shaderParams[actualProgram].prog);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(shaderParams[actualProgram].pos_loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
	glVertexAttribPointer(shaderParams[actualProgram].uv_loc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (GLvoid*)(sizeof(float)* 8));
	glEnableVertexAttribArray(shaderParams[actualProgram].pos_loc);
	glEnableVertexAttribArray(shaderParams[actualProgram].uv_loc);

	glUniform1i(shaderParams[actualProgram].tex1_loc, 0);
	glUniform1i(shaderParams[actualProgram].tex2_loc, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID1);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texID2);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void on_surface_created() {
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	changeEffect(actualProgram);
}

void on_surface_changed() {
    // No-op
}

void on_draw_frame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawQuad();
	glFinish();
}

void changeEffect(int i) {
	DPRINTF("Changing effect to: %s [%d]", effectsShaders[i],i);
	actualProgram = i;
}


void compileAllShaders() {
	if(areShadersLoaded == 0) {
		initQuad();
		DPRINTF("About to compile all shaders");
		for(int i=0; i < NUM_OF_SHADERS; i++) {
			DPRINTF("%s [%d]", effectsShaders[i],i);
			shaderParams[i].prog = build_program_from_assets("Shaders/basic.vs", effectsShaders[i]);
			shaderParams[i].pos_loc = glGetAttribLocation(shaderParams[i].prog, "vPosition");
			shaderParams[i].uv_loc = glGetAttribLocation(shaderParams[i].prog, "vUV");
			shaderParams[i].tex1_loc = glGetUniformLocation(shaderParams[i].prog, "tex");
			shaderParams[i].tex2_loc = glGetUniformLocation(shaderParams[i].prog, "tex2");
		}
		areShadersLoaded = 1;
	}
}




