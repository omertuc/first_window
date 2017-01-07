#include "window.h"
#include "render.h"
#include "graphics.h"
#include "texture.h"
#include "Game.h"

#include <chrono>


bool game_loop()
{
	Game my_game;
	if (!my_game.initialize())
	{
		print_error("Failed to initialize the game.");	
		return false;
	}

	GLFWwindow* current_window = glfwGetCurrentContext();
	if (current_window == nullptr)
	{
		print_error("Failed to get current window");
		return false;
	}

	uint64_t loop_count = 0;
	
	auto start = std::chrono::high_resolution_clock::now();
	while(!glfwWindowShouldClose(current_window))
	{
		glfwPollEvents();

		if (!render(my_game))
		{
			return false;
		}

		glfwSwapBuffers(current_window);

		loop_count++;
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> diff = end - start;

	std::cout << "The game took " << diff.count() << " seconds with " << loop_count << " frames." << std::endl;

	return true;
}

int main()
{
	int ret_val = 0;

	if (!initialize_libraries())
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


