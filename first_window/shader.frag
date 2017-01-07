#version 330 core

out vec4 color;

in vec3 our_color;
in vec2 our_texcoord;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;

void main()
{
    color = mix(texture(ourTexture0, our_texcoord),
				texture(ourTexture1, our_texcoord),
				0.4);
}
