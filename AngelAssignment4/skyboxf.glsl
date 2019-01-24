#version 440
in vec3 Normal;
in vec3 TexCoords;

out vec4 color;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
	//vec3 I = normalize(TexCoords - cameraPos);
	//vec3 R = reflect(I, normalize(Normal));
	color = texture(skybox, TexCoords);
}