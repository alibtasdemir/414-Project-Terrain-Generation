#pragma once
#include <vector>
#include <string>

#include <Angel_commons/Angel.h>

#include "CommonValues.h"

#include "Mesh.h"


class Skybox
{
public:
	Skybox();

	Skybox(std::vector<std::string> filenames, const char* vShader, const char* fShader);

	void DrawSkybox(mat4 viewMatrix, mat4 projectionMatrix, mat4 model, vec3 camPos);


	~Skybox();

private:
	Mesh* skyMesh;

	GLuint shader;
	GLuint textureId;
	GLuint uniformProjection, uniformView, uniformModel, uniformcamPos;
};

