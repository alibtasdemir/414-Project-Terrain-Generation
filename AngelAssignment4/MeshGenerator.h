#pragma once
#include <vector>
#include <Angel_commons/Angel.h>
#include "Mesh.h"

struct PreMesh
{
	std::vector<unsigned int> indices;
	std::vector<GLfloat> vertices;
};

PreMesh * CreateQuadPreMesh(vec3 v0, vec3 v1, vec3 v2, vec3 v3);

PreMesh * CreateTorusPreMesh();

PreMesh * CreateCubePreMesh(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength);
PreMesh * CreateArrowPreMesh(GLfloat centerX, GLfloat centerY, GLfloat centerZ);


PreMesh * PreMeshSum(PreMesh * p0, PreMesh * p1);
void DisplayPreMeshInfo(PreMesh * preMesh);
Mesh * CreateMesh(PreMesh * preMesh);
