#include "window.h"
#include "render.h"

bool game_loop()
{
	GLFWwindow* current_window = glfwGetCurrentContext();
	if (current_window == nullptr)
	{
		print_error("Failed to get current window");
		return false;
	}

	while(!glfwWindowShouldClose(current_window))
	{
		glfwPollEvents();

		if (!render())
		{
			return false;
		}

		glfwSwapBuffers(current_window);
	}

	return true;
}

int main()
{
	int ret_val = 0;

	if (!initialize_game())
	{
		print_error("Failed to initialize game");
		ret_val = -1;
		goto done;
	}

	if (!game_loop())
	{
		print_error("Game error");
		ret_val = -1;
		goto done;
	}

done:
	terminate_glfw();

	print_info("Press any key to close");
	getchar();
	return ret_val;
}

