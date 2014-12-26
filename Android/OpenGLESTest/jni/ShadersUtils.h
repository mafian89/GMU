/*
 * ShadersUtils.h
 *
 *  Created on: 21.12.2014
 *      Author: Tomas
 */
#include "Common.h"
#include "FileUtils.h"
#include <stdio.h>
#include <iostream>

#ifndef SHADERSUTILS_H_
#define SHADERSUTILS_H_

#define DPRINTF(...)  __android_log_print(ANDROID_LOG_DEBUG,"Shader",__VA_ARGS__)

GLuint compile_shader(const GLenum type, const GLchar* source, const GLint length);
GLuint link_program(const GLuint vertex_shader, const GLuint fragment_shader);
GLuint build_program(
	const GLchar * vertex_shader_source, const GLint vertex_shader_source_length,
	const GLchar * fragment_shader_source, const GLint fragment_shader_source_length);
GLuint build_program_from_assets(const char* vertex_shader_path, const char* fragment_shader_path);

#endif /* SHADERSUTILS_H_ */
