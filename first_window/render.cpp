#include "opengl.h"
#include "render.h"
#include "shaders.h"
#include "general.h"

double g_back_color = 0.0f;

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  


bool render()
{
	glClearColor(g_back_color, 1.0f - g_back_color, 0.5, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);  
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	return true;
}