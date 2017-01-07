#include "texture.h"

static bool import_texture(const std::string& file_path, GLuint& o_texture_id)
{
	// Load image from file.
	int width, height;
	unsigned char* image = SOIL_load_image(file_path.c_str(),
		&width, &height, 0, SOIL_LOAD_RGB); 

	if (image == nullptr)
	{
		print_error("Failed to open image file:");
		print_error(file_path.c_str());
		return false;
	}

	// Create new texture object.
	glGenTextures(1, &o_texture_id);
	glBindTexture(GL_TEXTURE_2D, o_texture_id);

	// Generate texture from the loaded image into the bound texture object.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, image);

	// Automatically generate mipmap.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free image data, unbind texture.
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

bool import_textures(const std::vector<const std::string>& files, 
					 std::vector<GLuint>& o_textures)
{
	for (auto it = files.begin(); it != files.end(); ++it)
	{
		GLuint texture;

		if (!import_texture(*it, texture))
		{
			return false;
		}

		o_textures.push_back(texture);
	}

	return true;
}