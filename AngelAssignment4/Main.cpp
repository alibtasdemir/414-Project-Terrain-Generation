#include "Main.h"

//////////////////////////////////////////////////////////
ShaderInfo* skyboxShader;
Mesh* skybox;

Texture cubeTexture;
Texture floorTexture;


void CreateTerrain() {
	Mesh *obj1 = GenerateTerrainMesh(80, 80, 0.1f);
	meshList.push_back(obj1);
}

Mesh* CreateCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength) {
	
	PreMesh* preMesh = CreateCubePreMesh(centerX, centerY, centerZ, edgeLength);
	Mesh* mesh = CreateMesh(preMesh);
	
	return mesh;
}





void init(){
	{ // creating shader program
		ShaderInfo* newShaderInfo = new ShaderInfo();

		program = InitShader("vshader.glsl", "fshader.glsl");
		newShaderInfo->program = program;
		
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
		newShaderInfo->u_time = glGetUniformLocation(program, "u_time");
		//std::cout << "[************u_time location at init(): " << newShaderInfo->u_time  << "]" << std::endl;
		printf("*******************uniform time: %i\n", newShaderInfo->u_time);
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

		//shaderInfoList.insert(shaderInfoList.end(), newShaderInfo);
		
		InteractableMesh* lightMesh = new InteractableMesh();
		lightMesh->mesh = CreateMesh(CreateArrowPreMesh(0, 0, 0));
		
		
		lightMesh->shaderInfo = newShaderInfo;
		lightMesh->interactable = new Interactable();
		lightMesh->interactable->position = vec3(0, 8, -5);
		lightMesh->interactable->UpdateTransform();
		//InteractableMeshList.push_back(testCube);
		mainLightInteractable = lightMesh;
	}
	{ // skybox
		skyboxShader = new ShaderInfo();

		program = InitShader("vSkybox.glsl", "fSkybox.glsl");
		skyboxShader->program = program;

		skyboxShader->uniformModel = glGetUniformLocation(program, "model");
		skyboxShader->uniformProjection = glGetUniformLocation(program, "projection");
		skyboxShader->uniformView = glGetUniformLocation(program, "view");
		uniformDirectionalLight.uniformColor = glGetUniformLocation(program, "directionalLight.base.color");
		uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(program, "directionalLight.base.ambientIntensity");
		uniformDirectionalLight.uniformDirection = glGetUniformLocation(program, "directionalLight.direction");
		uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(program, "directionalLight.base.diffuseIntensity");
		skyboxShader->uniformEyePos = glGetUniformLocation(program, "eyePosition");
		skyboxShader->uniformSpecularIntensity = glGetUniformLocation(program, "material.specularIntensity");
		skyboxShader->uniformShininess = glGetUniformLocation(program, "material.shininess");

		skybox = CreateCube(0, 0, 0, 300);
	}
	{
		// torus
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

		//shaderInfoList.insert(shaderInfoList.end(), newShaderInfo);

		InteractableMesh* torusMesh = new InteractableMesh();
		torusMesh->mesh = CreateMesh(CreateTorusPreMesh());// CreateCube(0, 0, 0, 1);
		torusMesh->shaderInfo = newShaderInfo;
		torusMesh->interactable = new Interactable();
		torusMesh->interactable->position = vec3(5, 3, -5);
		torusMesh->interactable->UpdateTransform();
		InteractableMeshList.push_back(torusMesh);
	}


	//createFloor();
	//CreateObjects();
	CreateTerrain();


	glClearColor(BLACK, 1);

}


void DrawObject(Mesh* mesh, Texture* texture, mat4 transformation, ShaderInfo* shaderInfo) {
	mat4 projection = Perspective(90.0f, (GLfloat)1.0f, 0.1f, 500.0f);
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


	GLfloat current_time = glutGet(GLUT_ELAPSED_TIME)*0.001;
	std::cout << "[u_time location: " << shaderInfo->u_time << "]" << std::endl;
	glUniform1fv(shaderInfo->u_time, 1, &current_time);

	glUniformMatrix4fv(shaderInfo->uniformProjection, 1, GL_TRUE, projection);
	glUniformMatrix4fv(shaderInfo->uniformView, 1, GL_TRUE, viewM);
	glUniform3f(shaderInfo->uniformEyePos, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

	glUniformMatrix4fv(shaderInfo->uniformModel, 1, GL_TRUE, transformation);
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
		vec4 lightDirection = -mainLightInteractable->interactable->transform[1] + vec4(0,0,0,2);
		vec3 lightDirectionV3 = vec3(lightDirection.x, lightDirection.y, lightDirection.z);
		
		mainLight.UpdateDirection(lightDirectionV3);
		//mainLightInteractable->interactable->UpdatePhysics();


		sunlight = dot(lightDirectionV3, vec3(0, -1, 0));
		sunlight = (sunlight + 1) / 2;
		
		mainLight.ambientIntensity = 0.2f * sunlight;
		if (sunlight > 0.6f) {
			mainLight.diffuseIntensity = ((sunlight - 0.6f) / 4) * 10;
		}
		else {
			// 1,0.6   to   1, 0
			mainLight.diffuseIntensity = 0;
		}
	}

	{
		//draw and move skybox
		vec4 eye = vec4(0,0,0,1);
		vec4 at = -mainLightInteractable->interactable->transform[1];
		//mat4 skyboxTransform = Translate(camera.getCameraPosition());
		vec4 camPos = camera.getCameraPosition();
		//mat4 skyboxTransform = LookAt(camPos, camPos - mainLightInteractable->interactable->transform[1], vec4(0, 1, 0, 1));
		mat4 skyboxTransform = Translate(camPos) * RotateZ(mainLightInteractable->interactable->rotation.z) * RotateY(mainLightInteractable->interactable->rotation.y) * RotateX(mainLightInteractable->interactable->rotation.x);
		//mat4 skyboxTransform = mat4(1);
		
		DrawObject(skybox, &floorTexture, skyboxTransform, skyboxShader);
	}
	

	glutPostRedisplay();
	glutSwapBuffers();

}

void DisplayMatrix(mat4 matrix) {
	for (int i = 0; i < 4; i++) {
		
	}
}
void idle() {

	GLfloat now = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = now - lastTime;					// In miliseconds
	lastTime = now;

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

	//glutSetCursor(GLUT_CURSOR_NONE);
	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);

	glewInit();
	glewExperimental = TRUE;

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
								0.1f, 0.5f,
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


	init();

	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseClick);
	
	glutMainLoop();


	return 1;
}


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

//GLfloat xChange, yChange;
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
