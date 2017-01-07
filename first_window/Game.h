#pragma once

#include "opengl.h"
#include <vector>
#include <memory>


class Game
{
public:
	Game();
	~Game();

	Game(Game&&);
	Game& operator=(Game&&);

	bool initialize();
	GLuint get_program() const;
	GLuint get_vao() const;
	const std::vector<GLuint>& get_textures() const;

private:
	struct impl;
	std::unique_ptr<impl> pimpl;
};
