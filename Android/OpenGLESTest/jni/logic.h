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

GLuint texID1,texID2;
extern int actualProgram;
extern int areShadersLoaded;

static const char* effectsShaders[] = {
		"Shaders/basic.frag",
		"Shaders/adaptive_threshold.frag",
		"Shaders/threshold.frag",
		"Shaders/bitwise_and.frag",
		"Shaders/bitwise_not_and.frag",
		"Shaders/bitwise_not.frag",
		"Shaders/bitwise_or.frag",
		"Shaders/bitwise_xor.frag",
		"Shaders/dilation.frag",
		"Shaders/erosion.frag",
		"Shaders/gaussian_filter.frag",
		"Shaders/mean_filter.frag",
		"Shaders/median_filter.frag"
};

#define NUM_OF_SHADERS 13

typedef struct shaderParams {
	GLuint prog;
	GLuint pos_loc, uv_loc, tex1_loc, tex2_loc;
}SHADER_PARAMS;
#endif /* LOGIC_H_ */

#ifdef __cplusplus
}
#endif
