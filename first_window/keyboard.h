#pragma once

#include "opengl.h"

#define GET_FKEY_NUMBER(FKEY_KEY_CODE) ((FKEY_KEY_CODE) - (GLFW_KEY_F1) + 1)
#define IS_FKEY(KEY_CODE) (!((KEY_CODE < GLFW_KEY_F1) || (KEY_CODE > GLFW_KEY_F25)))

void my_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);