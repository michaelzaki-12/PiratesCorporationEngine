#version 460 core
out vec4 FragColor;
in vec3 color;
in vec2 texcoord;
uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, texcoord);
};