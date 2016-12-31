#include "general.h"
#include "keyboard.h"
#include "render.h"
#include "window.h"

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
			g_back_color = std::min(0.1f * GET_FKEY_NUMBER(key), 1.0f);
		}
		else if (key == GLFW_KEY_V)
		{
			static bool is_enabled = false;
			is_enabled = !is_enabled;
			set_vsync(is_enabled);

			if (is_enabled) print_info("VSync has been enabled");
			else			print_info("VSync has been disabled");
		}
		else if (key == GLFW_KEY_M)
		{
			static bool is_enabled = false;
			is_enabled = !is_enabled;
			set_wireframe(is_enabled);

			if (is_enabled) print_info("Wireframe has been enabled");
			else			print_info("Wireframe has been disabled");
		}
	}
	else
	{
		// Nothing for now.
	}
}