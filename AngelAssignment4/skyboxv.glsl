#version 440

layout(location = 0) in vec3 pos;
layout(location = 2) in vec3 normal;

out vec3 TexCoords;
out vec3 Normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	TexCoords = vec3(model * vec4(pos, 1.0f));
	gl_Position = projection * view * model * vec4(pos, 1.0);
	Normal = mat3(transpose(inverse(model))) * normal;
}