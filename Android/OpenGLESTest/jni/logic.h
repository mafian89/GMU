/*
 * logic.h
 *
 *  Created on: 20.12.2014
 *      Author: Tomas
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef LOGIC_H_
#define LOGIC_H_

#include "Common.h"

void initQuad();
void drawQuad();
void on_surface_created();
void on_surface_changed();
void on_draw_frame();
void changeEffect(int);
void setProgram(const char * name, int i);
void compileAllShaders();
void compileAndSetTargetedShader(int i);
void initFBO();
void initRenderTex();
void initPointVBO(int w, int h);
void computeHistogram();

GLuint texID1,texID2,histogramTex;
int textureWidth,textureHeight;
extern int actualProgram;
extern int areShadersLoaded;

#define NUM_OF_SHADERS 13

static const char* effectsShaders[][NUM_OF_SHADERS] = {
		{"Shaders/basic.vs", "Shaders/basic.frag"},
		{"Shaders/basic.vs", "Shaders/adaptive_threshold.frag"},
		{"Shaders/basic.vs", "Shaders/threshold.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_and.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_not_and.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_not.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_or.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_xor.frag"},
		{"Shaders/basic.vs", "Shaders/dilation.frag"},
		{"Shaders/basic.vs", "Shaders/erosion.frag"},
		{"Shaders/basic.vs", "Shaders/gaussian_filter.frag"},
		{"Shaders/basic.vs", "Shaders/mean_filter.frag"},
		{"Shaders/basic.vs", "Shaders/median_filter.frag"}
};


typedef struct shaderParams {
	GLuint prog;
	GLuint pos_loc, uv_loc, tex1_loc, tex2_loc;
}SHADER_PARAMS;
#endif /* LOGIC_H_ */

#ifdef __cplusplus
}
#endif
