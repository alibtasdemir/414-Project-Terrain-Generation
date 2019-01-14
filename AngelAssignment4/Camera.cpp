#include "Camera.h"


Camera::Camera(){}

Camera::Camera(vec3 startPosition, vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();

}


void Camera::keyControl(unsigned char keys, GLfloat deltaTime) {

	GLfloat vel = moveSpeed * (deltaTime);
	
	// DEBUG ##################################################################################################
	printf("\n%f %f %f \n", position.x, position.y, position.z);
	//printf("\n%f %f %f \n", up.x, up.y, up.z);
	printf("\n%f %f %f \n", cross(front, worldUp).x, cross(front, worldUp).y, cross(front, worldUp).z);
    //#########################################################################################################


	if (keys == 'w')
	{
		position += front * vel;
	}

	if (keys == 's')
	{
		position -= front * vel;
	}

	if (keys == 'a')
	{
		position -= right * vel;
	}

	if (keys == 'd')
	{
		position += right * vel;
	}
}


mat4 Camera::calculateVievMatrix() {
	return (LookAt(position, position+ front, up));
}

void Camera::update() {

	GLfloat toRadian = M_PI / 180.0f;

	front.x = cos(yaw * toRadian) * cos(pitch * toRadian);
	front.y = sin(pitch * toRadian);
	front.z = sin(yaw * toRadian) * cos(pitch * toRadian);

	front = normalize(front);

	right = normalize(cross(front, worldUp));

	up = normalize(cross(right, front));
}

Camera::~Camera()
{
}
