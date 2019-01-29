#include "MeshGenerator.h"
PreMesh* CreateQuadPreMesh(vec3 v0, vec3 v1, vec3 v2, vec3 v3) {
			//    quad
			//   3   2
			//   0   1
	std::vector<GLfloat> vertices{
		v0.x, v0.y, v0.z, 0,0,0,0,0,
		v1.x, v1.y, v1.z, 1,0,0,0,0,
		v2.x, v2.y, v2.z, 1,1,0,0,0,
		v3.x, v3.y, v3.z, 0,1,0,0,0
	};
	std::vector<unsigned int> indices{
		0, 1, 2,
		0, 2, 3
	};

	PreMesh* quadPreMesh = new PreMesh();
	quadPreMesh->indices = indices;
	quadPreMesh->vertices = vertices;
	return quadPreMesh;
}
PreMesh* CreateTorusPreMesh() {
	float radius = 2;
	float thickness = 1;

	PreMesh* torusPreMesh = new PreMesh();
	float pi = 3.14159265f;
	vec3 center = vec3(0, 0, 0);
	float angleStep = pi / 10;

	

	float angleOut = 0;
	float angleIn = 0;
	for (angleOut = 0; angleOut <= pi * 2; angleOut += angleStep) {
		

		for (angleIn = 0; angleIn <= pi * 2; angleIn += angleStep) {
			std::vector<vec3> vertices = std::vector<vec3>();
			{ // v0
				float x = cos(angleOut) * radius;
				float z = sin(angleOut) * radius;
				vec3 forward = cross(vec3(x, 0, z), vec3(0, 1, 0)) * thickness;
				vec3 cutCenter = center + vec3(x, 0, z) * thickness;

				vec3 onOutDir = cos(angleIn) * (normalize(cutCenter));
				vec3 onUpDir = sin(angleIn) * vec3(0, 1, 0);
				vec3 onCut = cutCenter + onOutDir + onUpDir;
				vec3 v = onCut;
				vertices.push_back(v);
			}
			{ // v1
				float x = cos(angleOut + angleStep) * radius;
				float z = sin(angleOut + angleStep) * radius;
				vec3 forward = cross(vec3(x, 0, z), vec3(0, 1, 0)) * thickness;
				vec3 cutCenter = center + vec3(x, 0, z) * thickness;

				vec3 onOutDir = cos(angleIn) * (normalize(cutCenter));
				vec3 onUpDir = sin(angleIn) * vec3(0, 1, 0);
				vec3 onCut = cutCenter + onOutDir + onUpDir;
				vec3 v = onCut;
				vertices.push_back(v);
			}
			{ // v2
				float x = cos(angleOut) * radius;
				float z = sin(angleOut) * radius;
				vec3 forward = cross(vec3(x, 0, z), vec3(0, 1, 0)) * thickness;
				vec3 cutCenter = center + vec3(x, 0, z) * thickness;

				vec3 onOutDir = cos(angleIn + angleStep) * (normalize(cutCenter));
				vec3 onUpDir = sin(angleIn + angleStep) * vec3(0, 1, 0);
				vec3 onCut = cutCenter + onOutDir + onUpDir;
				vec3 v = onCut;
				vertices.push_back(v);
			}
			{ // v3
				float x = cos(angleOut + angleStep) * radius;
				float z = sin(angleOut + angleStep) * radius;
				vec3 forward = cross(vec3(x, 0, z), vec3(0, 1, 0)) * thickness;
				vec3 cutCenter = center + vec3(x, 0, z) * thickness;

				vec3 onOutDir = cos(angleIn + angleStep) * (normalize(cutCenter));
				vec3 onUpDir = sin(angleIn + angleStep) * vec3(0, 1, 0);
				vec3 onCut = cutCenter + onOutDir + onUpDir;
				vec3 v = onCut;
				vertices.push_back(v);
			}
			PreMesh* quadPreMesh = CreateQuadPreMesh(vertices[1], vertices[3], vertices[2], vertices[0]);
			torusPreMesh = PreMeshSum(torusPreMesh, quadPreMesh);
			
		}
	}

	return torusPreMesh;
}
PreMesh* CreateCubePreMesh(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength) {

	printf("Cube created at pos: %f, %f, %f \n", centerX, centerY, centerZ);

	GLfloat halfSideLength = edgeLength * 0.5f;

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};


	std::vector<GLfloat> vertices = {
		// front
//				X								Y					Z					u		v		nx	  ny	nz

		centerX - halfSideLength, centerY + halfSideLength, centerZ + halfSideLength,	0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-left
		centerX + halfSideLength, centerY + halfSideLength, centerZ + halfSideLength,	1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-right
		centerX + halfSideLength, centerY - halfSideLength, centerZ + halfSideLength,	1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-right
		centerX - halfSideLength, centerY - halfSideLength, centerZ + halfSideLength,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-left

		// back
		centerX - halfSideLength, centerY + halfSideLength, centerZ - halfSideLength,	0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-left
		centerX + halfSideLength, centerY + halfSideLength, centerZ - halfSideLength,	1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-right
		centerX + halfSideLength, centerY - halfSideLength, centerZ - halfSideLength,	1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-right
		centerX - halfSideLength, centerY - halfSideLength, centerZ - halfSideLength,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-left

		// left
		centerX - halfSideLength, centerY + halfSideLength, centerZ + halfSideLength,	0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-left
		centerX - halfSideLength, centerY + halfSideLength, centerZ - halfSideLength,	1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-right
		centerX - halfSideLength, centerY - halfSideLength, centerZ - halfSideLength,	1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-right
		centerX - halfSideLength, centerY - halfSideLength, centerZ + halfSideLength,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-left

		// right
		centerX + halfSideLength, centerY + halfSideLength, centerZ + halfSideLength,	0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-left
		centerX + halfSideLength, centerY + halfSideLength, centerZ - halfSideLength,	1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-right
		centerX + halfSideLength, centerY - halfSideLength, centerZ - halfSideLength,	1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-right
		centerX + halfSideLength, centerY - halfSideLength, centerZ + halfSideLength,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-left

		// top
		centerX - halfSideLength, centerY + halfSideLength, centerZ + halfSideLength,	0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-left
		centerX - halfSideLength, centerY + halfSideLength, centerZ - halfSideLength,	1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-right
		centerX + halfSideLength, centerY + halfSideLength, centerZ - halfSideLength,	1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-right
		centerX + halfSideLength, centerY + halfSideLength, centerZ + halfSideLength,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-left

		// bottom
		centerX - halfSideLength, centerY - halfSideLength, centerZ + halfSideLength,	0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-left
		centerX - halfSideLength, centerY - halfSideLength, centerZ - halfSideLength,	1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-right
		centerX + halfSideLength, centerY - halfSideLength, centerZ - halfSideLength,	1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-right
		centerX + halfSideLength, centerY - halfSideLength, centerZ + halfSideLength,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-left


	};

	PreMesh* preMesh = new PreMesh();
	preMesh->indices = indices;
	preMesh->vertices = vertices;
	return preMesh;
	/*
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 24 * 8, 12 * 3);
	calcNormals(indices, 12 * 3, vertices, 24 * 8, 8, 5);

	return obj1;
	*/
}
PreMesh * CreateArrowPreMesh(GLfloat centerX, GLfloat centerY, GLfloat centerZ)
{
	float halfSideLength = 0.5f;
	std::vector<GLfloat> vertices{
		//				X								Y					Z					u		v		nx	  ny	nz
		centerX - halfSideLength, centerY				  , centerZ + halfSideLength,	0.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-left        0
		centerX - halfSideLength, centerY                 , centerZ - halfSideLength,	1.0f, 1.0f,		0.0f, 0.0f, 0.0f,	// top-right       1
		centerX + halfSideLength, centerY				  , centerZ - halfSideLength,	1.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-right    2
		centerX + halfSideLength, centerY				  , centerZ + halfSideLength,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,	// bottom-left     3

		centerX                 , centerY - 1             , centerZ                 ,   0.0f, 0.0f,     0.0f, 0.0f, 0.0f                             
	};

	//  0  3    
	//  1  2

	std::vector<unsigned int> indices{
		0, 1, 2,
		2, 3, 0,

		4, 3, 0,
		4, 0, 1,
		4, 1, 2,
		4, 2, 3
	};

	PreMesh* pyramidPreMesh = new PreMesh();
	pyramidPreMesh->vertices = vertices;
	pyramidPreMesh->indices = indices;

	PreMesh* cube = CreateCubePreMesh(0, 0.5f, 0, 0.3f);
	//return pyramidPreMesh;
//	PreMesh* arrowPreMesh = PreMeshSum(pyramidPreMesh, cube); 
	PreMesh* arrowPreMesh = PreMeshSum(cube, pyramidPreMesh);
	
	/*
	std::cout << "pyramid" << std::endl;
	DisplayPreMeshInfo(pyramidPreMesh);
	std::cout << "cube" << std::endl;
	DisplayPreMeshInfo(cube);
	std::cout << "sum" << std::endl;
	DisplayPreMeshInfo(arrowPreMesh);
	*/
	return arrowPreMesh;
}
PreMesh * PreMeshSum(PreMesh * p0, PreMesh * p1)
{
	PreMesh * sum = new PreMesh();
	std::vector<float> p0v = p0->vertices;
	std::vector<unsigned int> p0i = p0->indices;

	std::vector<float> p1v = p1->vertices;
	std::vector<unsigned int> p1i = p1->indices;


	unsigned int indexOffset = p0v.size() / 8;

	std::vector<unsigned int> p1IndicesCopy = p1i;
	for (int i = 0; i < p1IndicesCopy.size(); i++) {
		p1IndicesCopy[i] += indexOffset;
	}

	sum->vertices.insert(sum->vertices.end(), p0v.begin(), p0v.end());
	sum->vertices.insert(sum->vertices.end(), p1v.begin(), p1v.end());

	sum->indices.insert(sum->indices.end(), p0->indices.begin(), p0->indices.end());
	sum->indices.insert(sum->indices.end(),p1IndicesCopy.begin(), p1IndicesCopy.end());
	
	return sum;

	// a.insert(a.end(), b.begin(), b.end());

}
void DisplayPreMeshInfo(PreMesh* preMesh) {
	std::cout << std::endl;
	std::cout << "------premesh info:" << std::endl;
	std::cout << "vertices count / 8: " << preMesh->vertices.size() / 8 << std::endl;
	/*
	std::cout << "vertices: " <<std::endl;
	for (int i = 0; i < preMesh->vertices.size()/8; i++) {
		std::cout << preMesh->vertices[i + 0] << "\t" <<
			preMesh->vertices[i + 1] << "\t" <<
			preMesh->vertices[i + 2] << "\t" <<
			preMesh->vertices[i + 3] << "\t" <<
			preMesh->vertices[i + 4] << "\t" <<
			preMesh->vertices[i + 5] << "\t" <<
			preMesh->vertices[i + 6] << "\t" <<
			preMesh->vertices[i + 7] << "\t" <<
			std::endl;
	}
	*/
	std::cout << "indices: " << std::endl;
	for (int i = 0; i < preMesh->indices.size() / 3; i++) {
		std::cout << preMesh->indices[3*i + 0] << "\t" <<
			preMesh->indices[3*i + 1] << "\t" <<
			preMesh->indices[3*i + 2] << "\t" <<
			std::endl;
	}
	std::cout << std::endl;
	

}

Mesh* CreateMesh(PreMesh* preMesh) {
	calcNormals(&preMesh->indices[0], preMesh->indices.size(), &preMesh->vertices[0], preMesh->vertices.size(), 8, 5);
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(&preMesh->vertices[0], &preMesh->indices[0], preMesh->vertices.size(), preMesh->indices.size());

	return obj1;
}


