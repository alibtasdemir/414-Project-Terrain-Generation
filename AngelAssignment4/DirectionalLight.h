#pragma once

#include "Light.h"

class DirectionalLight :
	public Light
{

public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir);

	void UpdateDirection(vec3 newDirection);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	~DirectionalLight();

private:

	vec3 direction;

};


