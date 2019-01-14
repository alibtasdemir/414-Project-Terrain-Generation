#include "TerrainMesh.h"



siv::PerlinNoise perlinNoise = siv::PerlinNoise(1);

float PerlinNoise(float x, float y) {
	return perlinNoise.octaveNoise(x, y, 0, 4);
}

Mesh* GenerateTerrainMesh(float sizeX, float sizeZ, float step)
{
	std::vector<vec3> vertices = std::vector<vec3>();
	std::vector<unsigned int> indices = std::vector<unsigned int>();

	int vertCountX = sizeX / step;
	int vertCountZ = sizeZ / step;

	vec3 startPos = vec3(-sizeX / 2, 0, -sizeZ / 2);
	vec3 stepX = vec3(step, 0, 0);
	vec3 stepZ = vec3(0, 0, step);

	int quadCounter = 0;
	for (int x = 0; x < vertCountX; x++) {
		for (int z = 0; z < vertCountZ; z++) {
			vec3 quadPos = startPos + stepX * x + stepZ * z;


			//vertices.insert(vertices.end(), position);
			//    quad
			//   2   3
			//   0   1
			vec3 v0 = quadPos;
			v0 += PerlinNoise(v0.x, v0.z) * vec3(0, 1, 0) + vec3(0, -1, 0);
			vec3 v1 = quadPos + vec3(1, 0, 0) * step;
			v1 += PerlinNoise(v1.x, v1.z) * vec3(0, 1, 0) + vec3(0, -1, 0);
			vec3 v2 = quadPos + vec3(0, 0, 1) * step;
			v2 += PerlinNoise(v2.x, v2.z) * vec3(0, 1, 0) + vec3(0, -1, 0);
			vec3 v3 = quadPos + vec3(1, 0, 1) * step;
			v3 += PerlinNoise(v3.x, v3.z) * vec3(0, 1, 0) + vec3(0, -1, 0);

			std::vector<vec3> quadVertices = { v0, v1, v2, v3 };
			vertices.insert(vertices.end(), quadVertices.begin(), quadVertices.end());

			unsigned int indicesStart = 4 * quadCounter;
			indices.insert(indices.end(), 0 + indicesStart);
			indices.insert(indices.end(), 1 + indicesStart);
			indices.insert(indices.end(), 3 + indicesStart);

			indices.insert(indices.end(), 3 + indicesStart);
			indices.insert(indices.end(), 2 + indicesStart);
			indices.insert(indices.end(), 0 + indicesStart);

			quadCounter++;
		}
	}

	int floatPerVert = 8; // 5

	int floatArrSize = floatPerVert * (vertices.size());
	std::vector<GLfloat> floatVertices = std::vector<GLfloat>(floatArrSize);

	for (int i = 0; i < vertices.size(); i++) {
		int floatArrIndex = i * floatPerVert;
		floatVertices[floatArrIndex + 0] = vertices[i].x;
		floatVertices[floatArrIndex + 1] = vertices[i].y;
		floatVertices[floatArrIndex + 2] = vertices[i].z;
		floatVertices[floatArrIndex + 3] = 0;
		floatVertices[floatArrIndex + 4] = 0;

		// normals
		floatVertices[floatArrIndex + 5] = 0;
		floatVertices[floatArrIndex + 6] = 0;
		floatVertices[floatArrIndex + 7] = 0;
	}

	calcNormals(&indices[0], indices.size(), &floatVertices[0], floatArrSize, 8, 5);

	Mesh *mesh = new Mesh();
	std::cout << "vertices size: " << floatVertices.size() << ",  indicesSize: " << indices.size();
	mesh->CreateMesh(&floatVertices[0], &indices[0], floatVertices.size(), indices.size());
	return mesh;
}
