#pragma once

#include <Angel_commons/Angel.h>

class Light
{
public:
	Light();
	
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);

	~Light();

public:

	vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

};

