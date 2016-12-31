#include "general.h"
#include "keyboard.h"

void my_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
    		glfwSetWindowShouldClose(window, GL_TRUE);
		}
		else if (IS_FKEY(key))
		{
			std::cout << "The pressed key is F" << GET_FKEY_NUMBER(key) << std::endl;
		}
	}
	else
	{
		// Nothing for now.
	}
}