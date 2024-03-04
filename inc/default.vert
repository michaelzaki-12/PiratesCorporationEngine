#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 texcoord;
out vec3 Normal;
out vec3 CurrentPos;

uniform float scale;
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
   CurrentPos = vec3(model * vec4(aPos, 1.0f));
   gl_Position = camMatrix * vec4(CurrentPos, 1.0f);
   color = aColor;
   texcoord = aTex;
   Normal = aNormal;
}