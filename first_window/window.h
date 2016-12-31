#pragma once

#include "general.h"
#include "opengl.h"

GLFWmonitor* get_primary_monitor();

bool init_glfw();

bool init_glew();

bool init_gl();

bool render();

bool game_loop();

void terminate_glfw();

bool initialize_game();

