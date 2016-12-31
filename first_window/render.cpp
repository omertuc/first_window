#include "opengl.h"
#include "render.h"
#include "shaders.h"
#include "general.h"

double g_back_color = 0.0f;

bool render(GLuint program, GLuint vao)
{
	glClearColor(g_back_color, 1.0f - g_back_color, 0.5, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);   
	glBindVertexArray(0);

	return true;
}