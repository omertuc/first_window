#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 our_color;
out vec2 our_texcoord;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
	our_color = vec3(color);
	our_texcoord = texCoord;
}