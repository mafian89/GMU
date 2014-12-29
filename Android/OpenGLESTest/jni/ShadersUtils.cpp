#include "ShadersUtils.h"

#define SHADER "Shader"

GLuint compile_shader(const GLenum type, const GLchar* source, const GLint length) {
	GLuint shader_object_id = glCreateShader(type);
	GLint compile_status;

	glShaderSource(shader_object_id, 1, (const GLchar **)&source, &length);
	glCompileShader(shader_object_id);
	glGetShaderiv(shader_object_id, GL_COMPILE_STATUS, &compile_status);

	if (compile_status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader_object_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar log_buffer[infoLogLength];
		glGetShaderInfoLog(shader_object_id, infoLogLength, 0, log_buffer);
		DPRINTF("COMPILE: %s", log_buffer);
	}
	return shader_object_id;
}

GLuint link_program(const GLuint vertex_shader, const GLuint fragment_shader) {
	GLuint program_object_id = glCreateProgram();
	GLint link_status;

	glAttachShader(program_object_id, vertex_shader);
	glAttachShader(program_object_id, fragment_shader);
	glLinkProgram(program_object_id);
	glGetProgramiv(program_object_id, GL_LINK_STATUS, &link_status);
	if (link_status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv (program_object_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar infoLog[infoLogLength];
		glGetProgramInfoLog (program_object_id, infoLogLength, 0, infoLog);
		DPRINTF("LINK: %s", infoLog);
	}

	return program_object_id;
}

GLuint build_program(
    const GLchar * vertex_shader_source, const GLint vertex_shader_source_length,
    const GLchar * fragment_shader_source, const GLint fragment_shader_source_length) {

	GLuint vertex_shader = compile_shader(
        GL_VERTEX_SHADER, vertex_shader_source, vertex_shader_source_length);
	GLuint fragment_shader = compile_shader(
        GL_FRAGMENT_SHADER, fragment_shader_source, fragment_shader_source_length);
	return link_program(vertex_shader, fragment_shader);
}
#define DPRINTF(...)  __android_log_print(ANDROID_LOG_DEBUG,"loading shaders",__VA_ARGS__)
GLuint build_program_from_assets(const char* vertex_shader_path, const char* fragment_shader_path) {

	const FileData vertex_shader_source = get_asset_data(vertex_shader_path);
	const FileData fragment_shader_source = get_asset_data(fragment_shader_path);
	//DPRINTF("%s",vertex_shader_source.data_length);
	const GLuint program_object_id = build_program(
		(const char *)vertex_shader_source.data, vertex_shader_source.data_length,
		(const char *)fragment_shader_source.data, fragment_shader_source.data_length);

	release_asset_data(&vertex_shader_source);
	release_asset_data(&fragment_shader_source);

	return program_object_id;
}
