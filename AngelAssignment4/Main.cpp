#include "Main.h"

// Shader Pointers ///////////////////////////////////////

std::vector<InteractableMesh*> InteractableMeshList = std::vector<InteractableMesh*>();
InteractableMesh* mainLightInteractable;

std::vector<ShaderInfo*> shaderInfoList;
//////////////////////////////////////////////////////////


Texture cubeTexture;
Texture floorTexture;

GLfloat xChange, yChange;


void CreateTerrain() {
	Mesh *obj1 = GenerateTerrainMesh(80, 80, 0.1f);
	meshList.push_back(obj1);
}

Mesh* CreateCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength) {
	
	printf("Cube created at pos: %f, %f, %f \n", centerX, centerY, centerZ);

	GLfloat halfSideLength = edgeLength * 0.5f;
	
	unsigned int indices[] = {
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
	
	
	GLfloat vertices[] = {
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

	calcNormals(indices, 12*3, vertices, 24*8, 8, 5);
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 24*8, 12 * 3);

	return obj1;
	//meshList.push_back(obj1);
}


void createFloor() {
	
	unsigned int indices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat vertices[] = {
		-20.0f, -1.0f, -20.0f,	0.0f,  0.0f,	0.0f, -1.0f, 0.0f,
		 20.0f, -1.0f, -20.0f,	20.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-20.0f, -1.0f,  20.0f,	0.0f,  20.0f,	0.0f, -1.0f, 0.0f,
		 20.0f, -1.0f,  20.0f,	20.0f, 20.0f,	0.0f, -1.0f, 0.0f	
	};

	Mesh *obj = new Mesh();
	obj->CreateMesh(vertices, indices, 32, 6);
	meshList.push_back(obj);

}

void CreateObjects(){
	GLfloat cube_size = 0.25f;
	GLfloat sep = 0.5f;

	for (size_t i = 0; i < 25; i++)
	{
		for (size_t j = 0; j < 25; j++) {
			CreateCube((-10.0f + (j * (cube_size + sep))), -1.0f + (cube_size * 0.5f), (10.0f - (i * (cube_size + sep))), cube_size);
		}
	}
}

void createSkybox() {
	//mat4 transformation;
	mat4 projection = Perspective(90.0f, (GLfloat)1.0f, 0.1f, 100.0f);
	// Update camera
	mat4 viewM = camera.calculateVievMatrix();
	mat4 transformation;


	skybox.DrawSkybox(viewM, projection, transformation, camera.getCameraPosition());

}

void init(){
	
	{ // creating shader program
		ShaderInfo* newShaderInfo = new ShaderInfo();

		program = InitShader("vshader.glsl", "fshader.glsl");
		newShaderInfo->program = program;
		
		// Get uniform locations.
		newShaderInfo->uniformModel = glGetUniformLocation(program, "model");
		newShaderInfo->uniformProjection = glGetUniformLocation(program, "projection");
		newShaderInfo->uniformView = glGetUniformLocation(program, "view");
		uniformDirectionalLight.uniformColor = glGetUniformLocation(program, "directionalLight.base.color");
		uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(program, "directionalLight.base.ambientIntensity");
		uniformDirectionalLight.uniformDirection = glGetUniformLocation(program, "directionalLight.direction");
		uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(program, "directionalLight.base.diffuseIntensity");
		newShaderInfo->uniformEyePos = glGetUniformLocation(program, "eyePosition");
		newShaderInfo->uniformSpecularIntensity = glGetUniformLocation(program, "material.specularIntensity");
		newShaderInfo->uniformShininess = glGetUniformLocation(program, "material.shininess");
		newShaderInfo->uniformTime = glGetUniformLocation(program, "time");

		// Insert shader to shaders list.
		shaderInfoList.insert(shaderInfoList.end(), newShaderInfo);
	}
	{ // creating shader program
		ShaderInfo* newShaderInfo = new ShaderInfo();

		program = InitShader("vshader2.glsl", "fshader2.glsl");
		newShaderInfo->program = program;
		std::cout << "program: " << program << std::endl;
		newShaderInfo->uniformModel = glGetUniformLocation(program, "model");
		newShaderInfo->uniformProjection = glGetUniformLocation(program, "projection");
		newShaderInfo->uniformView = glGetUniformLocation(program, "view");
		uniformDirectionalLight.uniformColor = glGetUniformLocation(program, "directionalLight.base.color");
		uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(program, "directionalLight.base.ambientIntensity");
		uniformDirectionalLight.uniformDirection = glGetUniformLocation(program, "directionalLight.direction");
		uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(program, "directionalLight.base.diffuseIntensity");
		newShaderInfo->uniformEyePos = glGetUniformLocation(program, "eyePosition");
		newShaderInfo->uniformSpecularIntensity = glGetUniformLocation(program, "material.specularIntensity");
		newShaderInfo->uniformShininess = glGetUniformLocation(program, "material.shininess");
		newShaderInfo->uniformTime = glGetUniformLocation(program, "time");
		//shaderInfoList.insert(shaderInfoList.end(), newShaderInfo);
		
		InteractableMesh* lightMesh = new InteractableMesh();
		lightMesh->mesh = CreateCube(0, 0, 0, 1);
		lightMesh->shaderInfo = newShaderInfo;
		lightMesh->interactable = new Interactable();
		lightMesh->interactable->position = vec3(0, 8, -5);
		lightMesh->interactable->UpdateTransform();
		//InteractableMeshList.push_back(testCube);
		mainLightInteractable = lightMesh;
	}

	//createFloor();
	//CreateObjects();
	
	CreateTerrain();


	glClearColor(BLACK, 1);

}



//Mesh* mesh, Texture texture, mat4 transformation, GLuint shader
void DrawObject(Mesh* mesh, Texture* texture, mat4 transformation, ShaderInfo* shaderInfo) {
	//mat4 transformation;
	mat4 projection = Perspective(90.0f, (GLfloat)1.0f, 0.1f, 100.0f);
	// Update camera
	mat4 viewM = camera.calculateVievMatrix();

	glUseProgram(shaderInfo->program);


	mainLight.UseLight(uniformDirectionalLight.uniformAmbientIntensity,
		uniformDirectionalLight.uniformColor,
		uniformDirectionalLight.uniformDiffuseIntensity,
		uniformDirectionalLight.uniformDirection);

	vec3 lowerLight = camera.getCameraPosition();
	lowerLight.y -= 0.3f;
	spotLight.SetFlash(lowerLight, camera.getCameraDirection());

	spotLight.UseLight(uniformSpotLight.uniformAmbientIntensity, uniformSpotLight.uniformColor,
		uniformSpotLight.uniformDiffuseIntensity, uniformSpotLight.uniformPosition, uniformSpotLight.uniformDirection,
		uniformSpotLight.uniformConstant, uniformSpotLight.uniformLinear, uniformSpotLight.uniformExponent,
		uniformSpotLight.uniformEdge);


	glUniformMatrix4fv(shaderInfo->uniformProjection, 1, GL_TRUE, projection);
	glUniformMatrix4fv(shaderInfo->uniformView, 1, GL_TRUE, viewM);
	glUniform3f(shaderInfo->uniformEyePos, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

	glUniformMatrix4fv(shaderInfo->uniformModel, 1, GL_TRUE, transformation);
	glUniform1f(shaderInfo->uniformTime, glutGet(GLUT_ELAPSED_TIME));
	texture->UseTexture();
	mesh->RenderMesh();
}
void DrawInteractableObject(InteractableMesh* interactableMesh, Texture* texture) {
	DrawObject(interactableMesh->mesh, texture, interactableMesh->interactable->transform, interactableMesh->shaderInfo);
}

float time = 0;
void display(void) {

	unsigned int clear3d = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	unsigned int clear2d = GL_COLOR_BUFFER_BIT;
	glClear(clear3d);
	time += deltaTime * 0.1f;
	
	createSkybox();

	mat4 transformation;// = Scale(vec3(1, 1, 1));
	DrawObject(meshList[0], &floorTexture, transformation, shaderInfoList[0]);

	// draw interactable meshes
	for (int i = 0; i < InteractableMeshList.size(); i++) {
		InteractableMesh* element = InteractableMeshList[i];
		DrawInteractableObject(element, &floorTexture);
	}

	{
		// handle and draw the interactable mesh for light source
		DrawInteractableObject(mainLightInteractable, &floorTexture);
		vec4 lightDirection = mainLightInteractable->interactable->transform[0];
		vec3 lightDirectionV3 = vec3(lightDirection.x, lightDirection.y, lightDirection.z);
		mainLight.UpdateDirection(lightDirectionV3);
	}

	glutPostRedisplay();
	glutSwapBuffers();

}


void idle() {

	GLfloat now = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = now - lastTime;					// In miliseconds
	lastTime = now;
	//SetCursorPos(window_height > 1, window_width > 1);

}

int main(int argc, char **argv) {


	glutInit(&argc, argv);
	unsigned int displayMode3d = GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA;
	unsigned int displayMode2d = GLUT_RGBA | GLUT_SINGLE;
	glutInitDisplayMode(displayMode3d);
	glutInitWindowSize(window_height, window_width);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	window = glutCreateWindow("Terrain Generation");

	glEnable(GL_DEPTH_TEST);

	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);

	glewInit();
	glewExperimental = TRUE;

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
								0.3f, 0.3f,
							0.0f, 0.0f, -1.0f);

	spotLight = SpotLight(0.0f, 1.0f, 1.0f,
							0.0f, 1.0f,
							0.0f, 0.0f, 0.0f,
							0.0f, -1.0f, 0.0f,
							0.3f, 0.2f, 0.1f,
							20.0f);


	// setting up camera
	camera = Camera(
		vec3(0.0f, 5.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		-90.0f, 0.0f, 5.0f, .2f			// Camera angle, Camera rotation, Step size, Mouse sensitivity 
	);

	// Textures
	cubeTexture = Texture("Textures/texture_cube.bmp");
	cubeTexture.LoadTexture();
	floorTexture = Texture("Textures/texture_ground.bmp");
	floorTexture.LoadTexture();

	shaderInfoList = std::vector<ShaderInfo*>();
	
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cloudtop_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cloudtop_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cloudtop_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cloudtop_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cloudtop_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cloudtop_ft.tga");

	skybox = Skybox(skyboxFaces, "skyboxv.glsl", "skyboxf.glsl");
	
	init();

	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseClick);

	glutMainLoop();

	return 1;
}

// Keyboard control
void keyboard(unsigned char key, int x, int y)
{

	switch (key) {
	
	case 'q':
		glutDestroyWindow(window);
		break;
	default:
		//printf("Key pressed");
		camera.keyControl(key, (deltaTime / 100.0f));
		break;
	}
	MoveSelectedInteractable(key);

	glutPostRedisplay();
	
}

void reshape(int w, int h)
{
	//  Notify that this is a GLUT Callback
	printf("GLUT: ");

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);


}

// Mouse control
void mouseMove(int x, int y) {
	
	GLfloat xChange = 0.0f, yChange = 0.0f;
		

	GLfloat middleX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	GLfloat middleY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	xChange = (GLfloat)x - middleX;
	yChange = middleY - (GLfloat)y;
	
	if (abs(xChange) > 25.0f || abs(yChange) > 25.0f) {
		xChange = 25.0f;
		yChange = 25.0f;
	}

	camera.mouseControl(xChange, yChange);
	
	glutPostRedisplay();
}


void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		SelectInteractable(camera.getCameraPosition(), camera.getCameraDirection());
	}
}
