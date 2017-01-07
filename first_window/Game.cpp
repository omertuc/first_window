#include "Game.h"

#include "window.h"
#include "render.h"
#include "graphics.h"
#include "texture.h"

struct Game::impl
{
	GLuint program;
	GLuint vao;
	std::vector<GLuint> textures;
};

Game::Game() : pimpl(new Game::impl()) {}

Game::~Game() { }

GLuint Game::get_program() const
{
	return pimpl->program;
}

GLuint Game::get_vao() const
{
	return pimpl->vao;
}

const std::vector<GLuint>& Game::get_textures() const
{
	return pimpl->textures;
}


bool Game::initialize()
{
	print_info("Initializing shaders...");
	if (!initialize_shaders(pimpl->program))
	{
		print_error("Failed to initialize shaders");
		return false;
	}

	print_info("Initializing vertices...");
	if (!initialize_vertices(pimpl->vao))
	{
		print_error("Failed to initialize vertices");
		return false;
	}

	std::vector<const std::string> texture_files;
	texture_files.push_back(std::string("water.jpg"));
	texture_files.push_back(std::string("wood.jpg"));

	print_info("Initializing textures...");
	if (!import_textures(texture_files, pimpl->textures))
	{
		print_error("Failed to initialize vertices");
		return false;
	}

	return true;
}


