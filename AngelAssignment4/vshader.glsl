#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
	gl_Position = (projection) * (view) * (model) * vec4(aPos, 1.0);
	ourColor = vec4(clamp(aPos, 0.0f, 1.0f), 1.0f);

	TexCoord = tex;

	Normal = mat3(transpose(inverse(model))) * norm;

	FragPos = (model * vec4(aPos, 1.0)).xyz;

}