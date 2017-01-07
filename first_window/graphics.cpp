#include "opengl.h"
#include "render.h"
#include "shaders.h"
#include "general.h"

static const size_t ERROR_LOG_LENGTH = 512;

static bool compile_shader(const GLchar* shader_source, GLuint shader_type,
						   GLuint& shader_id)
{
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
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);

	GLint linkage_success;
	glGetProgramiv(program_id, GL_LINK_STATUS, &linkage_success);

	if(!linkage_success) 
	{
		GLchar infoLog[ERROR_LOG_LENGTH];
		glGetProgramInfoLog(program_id, ERROR_LOG_LENGTH, NULL, infoLog);
		print_error("Shader linkage failed. Linkage error log:");
		print_error(infoLog);
		return false;
	}

	return true;
}

bool initialize_shaders(GLuint& program_id)
{
	bool return_value = false;
	GLuint vertex_shader_id = 0;
	GLuint fragment_shader_id = 0;

	// Compile vertex shader
	GLchar* vertex_shader_source = get_vertex_shader();
	if (vertex_shader_source == nullptr)
	{
		print_error("Vertex shader source is null");
		return_value = false;
		goto init_shaders_end;
	}

	if (!compile_shader(vertex_shader_source, GL_VERTEX_SHADER,
		vertex_shader_id))
	{
		print_error("Vertex shader compilation failed");
		return_value = false;
		goto init_shaders_end;
	}

	// Compile fragment shader
	GLchar* fragment_shader_source = get_fragment_shader();
	if (fragment_shader_source == nullptr)
	{
		print_error("Fragment shader source is null");
		return_value = false;
		goto init_shaders_end;
	}
	
	if (!compile_shader(fragment_shader_source, GL_FRAGMENT_SHADER,
		fragment_shader_id))
	{
		print_error("Fragment shader compilation failed");
		return_value = false;
		goto init_shaders_end;
	}

	if (!link_program(vertex_shader_id, fragment_shader_id, program_id))
	{
		print_error("Failed to link program");
		return_value = false;
		goto init_shaders_end;
	}

	return_value = true;

init_shaders_end:
	if (vertex_shader_id != 0)
		glDeleteShader(vertex_shader_id);

	if (fragment_shader_id != 0)
		glDeleteShader(fragment_shader_id);
	
	return return_value;
}

#define RND \
	(-1.0f + static_cast <float> (rand())  / \
	(        static_cast <float> (RAND_MAX / (2.0))))

#define RND_COL \
	(static_cast <float> (rand())  / \
	(static_cast <float> (RAND_MAX / (1.0))))

GLfloat vertices[] = {
    // Positions          // Colors           // Texture Coords
     1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
     1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
    -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
};

GLuint indices[] = {
	0, 1, 2, 3, 0, 2
}; 

bool initialize_vertices(GLuint& vao)
{

	glGenVertexArrays(1, &vao);  
	glBindVertexArray(vao);

	GLuint vbo[1];
	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);  
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);  

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);  

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(2);  

	glBindVertexArray(0);

	return true;
}