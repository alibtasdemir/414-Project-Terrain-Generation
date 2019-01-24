#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform float time;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
	//vec3 aPos2 = aPos;
	//if(aPos.y < 1.9)
	//aPos2 = vec3(aPos.x,1.9,aPos.z);
	
	float terrainYSize = 10;
	float u = (model * vec4(aPos, 1.0)).y;;
	float xs = 0.5, zs = 0.5, h = 1.0;
/*
	if (u < 0.2 * terrainYSize) {
		vec4 t = vec4(aPos, 1.0);
		t.y = aPos.y
			+ h * sin(time + xs * aPos.x)
			+ h * sin(time + zs * aPos.z);
	}*/

	gl_Position = (projection) * (view) * (model) * vec4(aPos, 1.0);
	ourColor = vec4(clamp(aPos, 0.0f, 1.0f), 1.0f);
	//ourColor = vec4(0,0,1,1);

	TexCoord = tex;

	Normal = mat3(transpose(inverse(model))) * norm;
	
	
	FragPos = (model * vec4(aPos, 1.0)).xyz;

}