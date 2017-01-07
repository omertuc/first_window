#pragma once

extern double g_back_color;

bool render(GLuint program, GLuint vao, GLuint texture);
void set_wireframe(bool enabled);
void set_texture_filtering_linear(bool enabled);