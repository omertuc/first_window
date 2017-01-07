#include "opengl.h"
#include "render.h"
#include "shaders.h"
#include "general.h"

double g_back_color = 0.0f;

void set_wireframe(bool enabled)
{
	glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

void set_texture_filtering_linear(bool enabled)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		enabled ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		enabled ? GL_LINEAR : GL_NEAREST);
}


bool render(GLuint program, GLuint vao, GLuint texture)
{
	glClearColor(g_back_color, 1.0f - g_back_color, 0.5, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   
	glBindVertexArray(0);

	return true;
}