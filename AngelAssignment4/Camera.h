#pragma once

#include <Angel_commons/Angel.h>
#include <math.h>

class Camera
{
public:

	Camera();

	Camera(vec3 startPosition, vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(unsigned char keys, GLfloat deltaTime);

	void mouseControl(GLfloat xChange, GLfloat yChange);

	vec3 getCameraPosition();
	vec3 getCameraDirection();

	mat4 calculateVievMatrix();

	~Camera();


private:
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void update();
};

