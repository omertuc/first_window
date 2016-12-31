#include "opengl.h"

bool render()
{
	glClearColor(0.2, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
		
	return true;
}