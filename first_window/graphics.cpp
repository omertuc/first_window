#include "opengl.h"
#include "render.h"
#include "shaders.h"
#include "general.h"

static const size_t ERROR_LOG_LENGTH = 512;

static bool compile_shader(const GLchar* shader_source, GLuint shader_type,
						   GLuint& shader_id)
{
	GLuint shader_id;
	shader_id = glCreateShader(shader_type);

	glShaderSource(shader_id, 1, &shader_source, NULL);
	glCompileShader(shader_id);

	GLint compilation_success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compilation_success);

	if(!compilation_success)
	{
		GLchar infoLog[ERROR_LOG_LENGTH];
		glGetShaderInfoLog(shader_id, ERROR_LOG_LENGTH, NULL, infoLog);
		print_error("Shader compilation failed. Compilation error log:");
		print_error(infoLog);
		return false;
	}

	return true;
}

static bool link_program(GLuint vertex_shader_id, GLuint fragment_shader_id,
						 GLuint& program_id)
{
	// Link both shaders
	GLuint shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader_id);
	glAttachShader(shader_program, fragment_shader_id);
	glLinkProgram(shader_program);

	GLint linkage_success;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &linkage_success);

	if(!linkage_success) 
	{
		GLchar infoLog[ERROR_LOG_LENGTH];
		glGetProgramInfoLog(shader_program, ERROR_LOG_LENGTH, NULL, infoLog);
		print_error("Shader linkage failed. Linkage error log:");
		print_error(infoLog);
		return false;
	}

	return true;
}

bool initialize_shaders()
{
	// Compile vertex shader
	GLchar* vertex_shader_source = get_vertex_shader();
	if (vertex_shader_source == nullptr)
	{
		print_error("Vertex shader source is null");
		return false;
	}

	GLuint vertex_shader_id = 0;
	if (!compile_shader(vertex_shader_source, GL_VERTEX_SHADER,
		vertex_shader_id))
	{
		print_error("Vertex shader compilation failed");
		return false;
	}

	// Compile fragment shader
	GLchar* fragment_shader_source = get_fragment_shader();
	if (fragment_shader_source == nullptr)
	{
		print_error("Fragment shader source is null");
		glDeleteShader(vertex_shader_id);
		return false;
	}

	GLuint fragment_shader_id = 0;
	if (!compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER),
		fragment_shader_id)
	{
		print_error("Fragment shader compilation failed");
		glDeleteShader(vertex_shader_id);
		return false;
	}

	GLuint program_id = 0;
	if (!link_program(vertex_shader_id, fragment_shader_id, program_id))
	{
		print_error("Failed to link program");
		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);
		return false;
	}

	glUseProgram(program_id);

	// Now that we have a program, we can discard the shaders.
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return true;
}