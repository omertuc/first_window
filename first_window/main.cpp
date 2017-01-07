#include "window.h"
#include "render.h"
#include "graphics.h"
#include "texture.h"

#include <time.h>

#include <chrono>

bool game_loop()
{
	GLuint program = 0;
	print_info("Initializing shaders...");
	if (!initialize_shaders(program))
	{
		print_error("Failed to initialize shaders");
		return false;
	}

	GLuint vao = 0;
	print_info("Initializing vertices...");
	if (!initialize_vertices(vao))
	{
		print_error("Failed to initialize vertices");
		return false;
	}

	GLuint texture = 0;
	print_info("Initializing textures...");
	if (!import_texture("wood.jpg", texture))
	{
		print_error("Failed to initialize vertices");
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

		if (!render(program, vao, texture))
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

