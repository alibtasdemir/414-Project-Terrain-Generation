#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 vCol;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform float u_time;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

float waveMotion(float position, float time, float hscale, float f_x, float f_z) {
	position = aPos.y + hscale * sin(time + f_x * aPos.x) + hscale * sin(time + f_z * aPos.z);
	return position;
}

void main() {
	
	vec3 pos = aPos;
	
	float terrainYSize = 10.0f;
	float u = ((model * vec4(pos, 1.0f)).y);

	if (u <= 0.2 * terrainYSize) {
		//pos.y = waveMotion(pos.y, u_time, 0.1f, 0.02f, 0.02f);
	}
	
	gl_Position = (projection) * (view) * (model) * vec4(pos, 1.0f);
	//vCol = vec4(clamp(aPos, 0.0f, 1.0f), 1.0f);
	//ourColor = vec4(0,0,1,1);

	TexCoord = tex;

	Normal = mat3(transpose(inverse(model))) * norm;

	FragPos = (model * vec4(aPos, 1.0f)).xyz;

}