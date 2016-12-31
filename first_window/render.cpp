#include "opengl.h"
#include "render.h"
#include "shaders.h"
#include "general.h"

double g_back_color = 0.0f;

void set_wireframe(bool enabled)
{
	glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

bool render(GLuint program, GLuint vao)
{
	glClearColor(g_back_color, 1.0f - g_back_color, 0.5, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   
	glBindVertexArray(0);

	return true;
}