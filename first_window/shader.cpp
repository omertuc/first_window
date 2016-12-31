#include <stdio.h>
#include "general.h"

static char* read_entire_file(char* file_path)
{
	FILE* file_pointer = fopen(file_path, "rb");
	if (file_pointer == nullptr)
	{
		print_error("Failed to open file:");
		print_error(file_path);
		return nullptr;
	}

	fseek(file_pointer, 0L, SEEK_END);
	size_t file_size = ftell(file_pointer);
	rewind(file_pointer);

	char* file_buffer = new char[file_size];
	if (file_buffer == nullptr)
	{
		print_error("Failed to allocate buffer for file:");
		print_error(file_path);
		fclose(file_pointer);
		return nullptr;
	}

	size_t actual_read = 
		fread(file_buffer, sizeof(char), file_size, file_pointer);

	if (actual_read != file_size)
	{
		print_error("Failed to read entire file:");
		print_error(file_path);
		fclose(file_pointer);
		return nullptr;
	}

	fclose(file_pointer);
	return file_buffer;
}

char* get_vertex_shader()
{
	static char* shader =
		read_entire_file("shaders\\shader.vert");

	return shader;
}

char* get_fragment_shader()
{
	static char* shader =
		read_entire_file("shaders\\shader.frag");

	return shader;
}

