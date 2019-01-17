#define STB_IMAGE_IMPLEMENTATION

#include <Angel_commons/Angel.h>
#include <vector>


#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "TerrainMesh.h"

#define GREEN 0.0f, 0.683f, 0.3125f
#define BLACK 0.0f, 0.0f, 0.0f
#define RED 0.99218f, 0.0f, 0.0f


// Function predefinitions. //////////////////////////////
void mouseMove(int x, int y);						//////
void reshape(int w, int h);							//////
void keyboard(unsigned char key, int x, int y);		//////
//////////////////////////////////////////////////////////


// Shader Pointers ///////////////////////////////////////
struct {								
	GLuint uniformColor;
	GLuint uniformAmbientIntensity;
	GLuint uniformDiffuseIntensity;

	GLuint uniformDirection;
} uniformDirectionalLight;

struct {
	GLuint uniformColor;
	GLuint uniformAmbientIntensity;
	GLuint uniformDiffuseIntensity;

	GLuint uniformPosition;
	GLuint uniformConstant;
	GLuint uniformLinear;
	GLuint uniformExponent;

	GLuint uniformDirection;
	GLuint uniformEdge;
} uniformSpotLight;

GLuint uniformModel = 0, uniformProjection = 0, 
uniformView = 0, uniformEyePos = 0, 
uniformSpecularIntensity = 0, uniformShininess = 0;
//////////////////////////////////////////////////////////


std::vector<Mesh*> meshList;
Camera camera;

Texture cubeTexture;
Texture floorTexture;

GLfloat xChange, yChange;
DirectionalLight mainLight;

SpotLight spotLight;


//  variables representing the window size
int window_height = 1366,
		window_width = 768;
const float toRadians = 3.14159265f / 180.0f;


int window;					// glut window.

GLuint program;				// Shader program.

GLfloat deltaTime = 0.0f, lastTime = 0.0f;



void CreateTerrain() {
	Mesh *obj1 = GenerateTerrainMesh(80, 80, 0.1f);
	meshList.push_back(obj1);
}
void CreateCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength) {
	
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
	meshList.push_back(obj1);
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

void init(){

	program = InitShader("vshader.glsl", "fshader.glsl");
	std::cout << "program: " << program << std::endl;
	uniformModel = glGetUniformLocation(program, "model");
	uniformProjection = glGetUniformLocation(program, "projection");
	uniformView = glGetUniformLocation(program, "view");
	uniformDirectionalLight.uniformColor = glGetUniformLocation(program, "directionalLight.base.color");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(program, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(program, "directionalLight.direction");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(program, "directionalLight.base.diffuseIntensity");
	uniformEyePos = glGetUniformLocation(program, "eyePosition");
	uniformSpecularIntensity = glGetUniformLocation(program, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(program, "material.shininess");

	
	//createFloor();
	//CreateObjects();
	CreateTerrain();

	glClearColor(BLACK, 1);

}
//Mesh* mesh, Texture texture, mat4 transformation, GLuint shader
void DrawObject(Mesh* mesh, Texture* texture, mat4 transformation, GLuint shader) {
	//mat4 transformation;
	mat4 projection = Perspective(90.0f, (GLfloat)1.0f, 0.1f, 100.0f);
	// Update camera
	mat4 viewM = camera.calculateVievMatrix();

	glUseProgram(shader);

	


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


	glUniformMatrix4fv(uniformProjection, 1, GL_TRUE, projection);
	glUniformMatrix4fv(uniformView, 1, GL_TRUE, viewM);
	glUniform3f(uniformEyePos, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

	glUniformMatrix4fv(uniformModel, 1, GL_TRUE, transformation);
	texture->UseTexture();
	mesh->RenderMesh();
}
void display(void) {

	unsigned int clear3d = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	unsigned int clear2d = GL_COLOR_BUFFER_BIT;
	glClear(clear3d);
	
	mat4 transformation;// = Scale(vec3(1, 1, 1));
	DrawObject(meshList[0], &floorTexture, transformation, 1);

	//transformation = RotateY(45);
	//DrawObject(meshList[0], &floorTexture, transformation, 1);

	glutPostRedisplay();
	glutSwapBuffers();

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

	window = glutCreateWindow("Ali Baran Tasdemir");

	glEnable(GL_DEPTH_TEST);

	glutSetCursor(GLUT_CURSOR_NONE);

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
		vec3(0.0f, 2.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		-90.0f, 0.0f, 5.0f, .2f			// Camera angle, Camera rotation, Step size, Mouse sensitivity 
	);

	// Textures
	cubeTexture = Texture("Textures/texture_cube.bmp");
	cubeTexture.LoadTexture();
	floorTexture = Texture("Textures/texture_ground.bmp");
	floorTexture.LoadTexture();


	init();

	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);

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

GLfloat lastx = 0.0f;
GLfloat lasty = 0.0f;

void mouseMove(int x, int y) {
	
	GLfloat xChange = 0.0f, yChange = 0.0f;
		
	xChange = (GLfloat)x - lastx;
	yChange = lasty - (GLfloat)y;

	
	if (abs(xChange) > 25.0f || abs(yChange) > 25.0f) {
		xChange = 25.0f;
		yChange = 25.0f;
	}

	camera.mouseControl(xChange, yChange);

	lastx = (GLfloat)x;
	lasty = (GLfloat)y;

	glutPostRedisplay();
}