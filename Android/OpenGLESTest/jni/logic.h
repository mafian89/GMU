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

GLuint texID1,texID2;

#endif /* LOGIC_H_ */

#ifdef __cplusplus
}
#endif
