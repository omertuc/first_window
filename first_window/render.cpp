#include "opengl.h"
#include "render.h"
#include "shaders.h"
#include "general.h"

double g_back_color = 0.0f;

void set_wireframe(bool enabled)
{
	glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

void set_texture_filtering_linear(bool enabled)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		enabled ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		enabled ? GL_LINEAR : GL_NEAREST);
}

#include <sstream>
static void bind_textures(const std::vector<GLuint>& textures, GLuint program)
{
	for (auto it = textures.begin(); it != textures.end(); ++it) 
	{
		int index = std::distance(textures.begin(), it);

		std::stringstream sstm;
		sstm << "ourTexture" << index;
		std::string text_var_name = sstm.str();

		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, *it);
		glUniform1i(glGetUniformLocation(program, text_var_name.c_str()), index);
	}
}

bool render(const Game& game)
{
	glClearColor(g_back_color, 1.0f - g_back_color, 0.5, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(game.get_program());
	glBindVertexArray(game.get_vao());
	bind_textures(game.get_textures(), game.get_program());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   
	glBindVertexArray(0);

	return true;
}