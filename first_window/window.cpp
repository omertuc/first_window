#include "general.h"
#include "opengl.h"
#include "window.h"
#include "keyboard.h"

GLFWmonitor* get_primary_monitor()
{
	int num_of_monitors = 0;
	GLFWmonitor** monitors = glfwGetMonitors(&num_of_monitors);

	if (num_of_monitors == 0)
	{
		print_error("No monitors found");
		return nullptr;
	}

	// The primary monitor is always the first.
	return monitors[1];
}

void my_focus_callback(GLFWwindow* window, int focus_state)
{
	// We gained focus...
	if (focus_state)
	{
		print_info("Gained focus");

		glfwMakeContextCurrent(window);
	}

	return;
}

void set_vsync(bool state)
{
	glfwSwapInterval(state ? 1 : 0);
}

bool init_glfw()
{
	if (glfwInit() != GLFW_TRUE)
	{
		return false;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWmonitor* monitor = get_primary_monitor();
	GLFWwindow* share = nullptr;

	if (monitor == nullptr)
	{
		print_error("Failed to get primary monitor");
		return false;
	}

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	
	if (mode == nullptr)
	{
		print_error("Failed to get video mode");
		return false;
	}

	int window_width = mode->width;
	int window_height = mode->height;

	GLFWwindow* window = glfwCreateWindow(window_width, window_height,
			"FirstWindow", monitor, share);

	if (window == nullptr)
	{
		print_error("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}

	glfwSetKeyCallback(window, my_key_callback);
	glfwSetWindowFocusCallback(window, my_focus_callback);

	glfwMakeContextCurrent(window);

	set_vsync(true);

	return true;
}

bool init_glew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		print_error("glewInit() failed");
		return false;
	}

	return true;
}

bool init_gl()
{
	if (!update_viewport())
	{
		return false;
	}

	return true;
}

bool update_viewport()
{
	GLFWwindow* current_window = glfwGetCurrentContext();
	if (current_window == nullptr)
	{
		print_error("Failed to get current window");
		return false;
	}

	int width, height;
	glfwGetFramebufferSize(current_window, &width, &height);
	glViewport(0, 0, width, height);

	return true;
}

void terminate_glfw()
{
	glfwTerminate();
}

bool initialize_game()
{
	print_info("Initializing GLFW...");
	if (!init_glfw())
	{
		print_error("Failed to initialize GLFW");
		return false;
	}

	print_info("Initializing GLEW...");
	if (!init_glew())
	{
		print_error("Failed to initialize GLEW");
		return false;
	}

	print_info("Initializing OpenGL...");
	if (!init_gl())
	{
		print_error("Failed to initialize OpenGL");
		return false;
	}

	print_info("All done");

	return true;
}

