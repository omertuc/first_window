#pragma once

#include "opengl.h"
#include "general.h"

bool import_textures(const std::vector<const std::string>& files, 
					 std::vector<GLuint>& o_textures);