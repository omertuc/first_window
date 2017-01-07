#version 330 core

out vec4 color;

in vec3 our_color;
in vec2 our_texcoord;

uniform sampler2D ourTexture;

void main()
{
    color = texture(ourTexture, our_texcoord) * gl_PointCoord.xyxx;
}
