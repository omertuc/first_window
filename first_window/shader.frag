out vec4 color;
in vec3 our_color;

void main()
{
    color = vec4(our_color, 1.0f);
} 