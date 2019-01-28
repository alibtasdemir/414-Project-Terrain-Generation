#include "Skybox.h"



Skybox::Skybox()
{
}

Skybox::Skybox(std::vector<std::string> filenames, const char * vShader, const char * fShader)
{
	shader = InitShader(vShader, fShader);
	uniformProjection = glGetUniformLocation(shader, "projection");
	uniformView = glGetUniformLocation(shader, "view");
	uniformcamPos = glGetUniformLocation(shader, "cameraPos");
	uniformModel = glGetUniformLocation(shader, "model");

	//
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	int width, height, bitDepth;
	for (size_t i = 0; i < 6; i++)
	{
		unsigned char* texdata = stbi_load(filenames[i].c_str(), &width, &height, &bitDepth, 0);
		if (!texdata)
		{
			printf("Failed to find: %s\n", filenames[i].c_str());
			return;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata);
		stbi_image_free(texdata);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//
	unsigned int skyboxIndices[] = {
		// front
		0, 1, 2,
		2, 1, 3,
		// right
		2, 3, 5,
		5, 3, 7,
		// back
		5, 7, 4,
		4, 7, 6,
		// left
		4, 6, 0,
		0, 6, 1,
		// top
		4, 0, 5,
		5, 0, 2,
		// bottom
		1, 6, 3,
		3, 6, 7
	};
	/*
	float skyboxVertices[] = {
		-1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f
	};*/

	float skyboxVertices[] = {
		-50.0f, 50.0f, -50.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		-50.0f, -50.0f, -50.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		50.0f, 50.0f, -50.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		50.0f, -50.0f, -50.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

		-50.0f, 50.0f, 50.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		50.0f, 50.0f, 50.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		-50.0f, -50.0f, 50.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		50.0f, -50.0f, 50.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f
	};

	calcNormals(skyboxIndices, 36, skyboxVertices, 64, 8, 5);
	skyMesh = new Mesh();
	skyMesh->CreateMesh(skyboxVertices, skyboxIndices, 64, 36);

}

void Skybox::DrawSkybox(mat4 viewMatrix, mat4 projectionMatrix, mat4 model, vec3 camPos)
{
	//viewMatrix = mat4(mat3(viewMatrix));

	glDepthMask(GL_FALSE);

	glUseProgram(shader);

	//printf("Skybox: Cam Pos. %f, %f, %f\n", camPos.x, camPos.y, camPos.z);
	glUniformMatrix4fv(uniformProjection, 1, GL_TRUE, projectionMatrix);
	glUniformMatrix4fv(uniformView, 1, GL_TRUE, viewMatrix);
	glUniformMatrix4fv(uniformModel, 1, GL_TRUE, model);
	glUniform3fv(uniformcamPos, 1, camPos);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	skyMesh->RenderMesh();

	glDepthMask(GL_TRUE);

}




Skybox::~Skybox()
{
}
