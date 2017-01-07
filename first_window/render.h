#pragma once

#include <vector>
#include "Game.h"

extern double g_back_color;

bool render(const Game& game);
void set_wireframe(bool enabled);
void set_texture_filtering_linear(bool enabled);