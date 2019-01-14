#define STB_IMAGE_IMPLEMENTATION

#include <Angel_commons/Angel.h>
#include <vector>
#include <assimp/Importer.hpp>


#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Model.h"
#include "PerlinNoise.h"
#include "TerrainMesh.h"

#define GREEN 0.0f, 0.683f, 0.3125f
#define BLACK 0.0f, 0.0f, 0.0f
#define RED 0.99218f, 0.0f, 0.0f

// Function predefinitions. ///////////////////////
void SpecialKeyboardCB(int Key, int x, int y);
void mouseMove(int x, int y);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
//////////////////////////////////////////////////


std::vector<Mesh*> meshList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;

GLfloat xChange, yChange;
Model model;


//  variables representing the window size
int window_width = 800, window_height = 800;
const float toRadians = 3.14159265f / 180.0f;

GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0;

int window;					// glut window.

GLuint program;				// Shader program.

GLfloat deltaTime = 0.0f, lastTime = 0.0f;


// ----------

int frameCount = 0;

void CreateObjects(){
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v
			-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,
			1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = GenerateTerrainMesh(10,10,0.2f);
	meshList.push_back(obj3);
}

void init(){

	program = InitShader("vshader.glsl", "fshader.glsl");

	uniformModel = glGetUniformLocation(program, "model");
	uniformProjection = glGetUniformLocation(program, "projection");
	uniformView = glGetUniformLocation(program, "view");

	CreateObjects();

	glClearColor(BLACK, 1);

}


void display(void){
	
	unsigned int clear3d = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	unsigned int clear2d = GL_COLOR_BUFFER_BIT;

	

	//printf("Window width %d\n", GLUT_WINDOW_WIDTH);
	mat4 transformation;
	mat4 projection = Perspective(45.0f, (GLfloat)1.0f, 0.1f, 100.0f);
	// Update camera
	mat4 viewM = camera.calculateVievMatrix();

	glUseProgram(program);

	glClear(clear3d);

	mat4 T = Translate(vec3(0.0f, 0.0f, -2.5f));
	mat4 S = Scale(vec3(0.4f, 0.4f, 1.0f));

	transformation = S * T;

	glUniformMatrix4fv(uniformModel, 1, GL_TRUE, transformation);
	glUniformMatrix4fv(uniformProjection, 1, GL_TRUE, projection);
	glUniformMatrix4fv(uniformView, 1, GL_TRUE, viewM);
	brickTexture.UseTexture();
	meshList[0]->RenderMesh();

	
	T = Translate(vec3(0.0f, 1.0f, -2.5f));
	S = Scale(vec3(0.4f, 0.4f, 1.0f));
	transformation = S * T;

	glUniformMatrix4fv(uniformModel, 1, GL_TRUE, transformation);
	dirtTexture.UseTexture();
	meshList[1]->RenderMesh();

	transformation = mat4(1);
	glUniformMatrix4fv(uniformModel, 1, GL_TRUE, transformation);
	dirtTexture.UseTexture();
	meshList[2]->RenderMesh();

	
	frameCount++;
	//S = Scale(vec3(0.4f, 0.4f, 1.0f));

	//transformation = T;

	//glUniformMatrix4fv(uniformModel, 1, GL_TRUE, transformation);
	//model.RenderModel();

	glutPostRedisplay();
	glutSwapBuffers();

}


void idle() {

	GLfloat now = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = now - lastTime;
	lastTime = now;

	//printf("Delta time is %f\n", deltaTime / 100.0f);
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

	glewInit();


	// setting up camera
	camera = Camera(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f),
		-90.0f, 0.0f, .01f, .02f
	);

	// Textures
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTexture();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTexture();

	//model = Model();
	//model.LoadModel("Textures/dragon_10k.obj");

	init();

	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	//glutMotionFunc(mouseMove);
	//glutPassiveMotionFunc(mouseMove);
	//glutSpecialFunc(SpecialKeyboardCB);

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
		printf("Key pressed");
		camera.keyControl(key, deltaTime);
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
/*
GLfloat lastx = 0.0f;
GLfloat lasty = 0.0f;

void mouseMove(int x, int y) {
	
	printf("Cursor x: %d, Cursor y: %d\n", x, y);
	GLfloat xChange = 0.0f, yChange = 0.0f;
		
	xChange = lastx - (GLfloat)x;
	yChange = lasty - (GLfloat)y;

	if (abs(xChange) > 25.0f || abs(yChange) > 25.0f) {
		xChange = 25.0f;
		yChange = 25.0f;
	}

	camera.mouseControl(xChange, yChange);

	lastx = (GLfloat)x;
	lasty = (GLfloat)y;

	glutPostRedisplay();
}*/