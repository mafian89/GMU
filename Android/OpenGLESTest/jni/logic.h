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
void drawQuad(GLuint prog, int v_coord_flipped);
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

GLuint texID1,texID2,histogramTex,renderTex,offsetXTex, offsetYTex;
int textureWidth,textureHeight;
int displayWidth, displayHeight;
extern int actualProgram;
extern int areShadersLoaded;

extern int kernelSize3, kernelLength3;
extern int kernelSize5, kernelLength5;
extern int kernelSize11, kernelLength11;

#define NUM_OF_SHADERS 23

static const char* effectsShaders[][NUM_OF_SHADERS] = {
		{"Shaders/basic.vs", "Shaders/basic.frag"},
		{"Shaders/basic.vs", "Shaders/basic_mask.frag"},
		{"Shaders/basic.vs", "Shaders/threshold.frag"},
		{"Shaders/basic.vs", "Shaders/adaptive_threshold_mean.frag"},
		{"Shaders/basic.vs", "Shaders/adaptive_threshold_meanC.frag"},
		{"Shaders/basic.vs", "Shaders/adaptive_threshold_median.frag"},
		{"Shaders/basic.vs", "Shaders/adaptive_threshold_minMax.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_and.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_or.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_xor.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_not.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_nand.frag"},
		{"Shaders/basic.vs", "Shaders/bitwise_nor.frag"},
		{"Shaders/basic.vs", "Shaders/dilation.frag"},
		{"Shaders/basic.vs", "Shaders/erosion.frag"},
		{"Shaders/basic.vs", "Shaders/opening.frag"},
		{"Shaders/basic.vs", "Shaders/closing.frag"},
		{"Shaders/basic.vs", "Shaders/mean_filter.frag"},
		{"Shaders/basic.vs", "Shaders/median_filter.frag"},
		{"Shaders/basic.vs", "Shaders/gaussian_filter.frag"},
		{"Shaders/basic.vs", "Shaders/gaussian_filterX.frag"},
		{"Shaders/basic.vs", "Shaders/gaussian_filterY.frag"},
		{"Shaders/basic.vs", "Shaders/adaptive_threshold_meanC_textures_offset.frag"}
};


typedef struct shaderParams {
	GLuint prog;
	GLuint pos_loc, uv_loc, tex1_loc, tex2_loc, v_coord_flipped_loc;
	GLuint offset3_loc, offset5_loc, offset11_loc, offset5_1D_X, offset5_1D_Y;
	GLuint offsetX_loc, offsetY_loc;
}SHADER_PARAMS;
#endif /* LOGIC_H_ */

#ifdef __cplusplus
}
#endif
