#pragma once
// Definitions
#define STB_IMAGE_IMPLEMENTATION
#define GREEN 0.0f, 0.683f, 0.3125f
#define BLACK 0.0f, 0.0f, 0.0f
#define RED 0.99218f, 0.0f, 0.0f
#define toRadians 3.14159265f / 180.0f

// Includes
#include <Angel_commons/Angel.h>
#include <vector>

#include "CommonValues.h"

#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "TerrainMesh.h"
#include "Interactables.h"
#include "Skybox.h"

// Structs
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

struct ShaderInfo {
	GLuint program = 0;
	GLuint uniformModel = 0, uniformProjection = 0,
		uniformView = 0, uniformEyePos = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTime = 0;
};

struct InteractableMesh {
	ShaderInfo* shaderInfo;
	Mesh* mesh;
	Interactable* interactable;
};

// Global Variables
std::vector<Mesh*> meshList;
Camera camera;

DirectionalLight mainLight;

SpotLight spotLight;
Skybox skybox;

int window_height = 1366,
window_width = 768;

int window;					// glut window.

GLuint program;				// Shader program.

GLfloat deltaTime = 0.0f, lastTime = 0.0f;

// Function prototypes.
void mouseMove(int x, int y);                       
void mouseClick(int button, int state, int x, int y);
void reshape(int w, int h);							
void keyboard(unsigned char key, int x, int y);	


