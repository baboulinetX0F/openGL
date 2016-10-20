#pragma once

#include <GL\glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

enum CameraDirection
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat MOVE_SPEED = 0.15f;
const GLfloat MOUSE_SENS = 0.05f;

class Camera
{
public:
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _pos;
	GLfloat _yaw;
	GLfloat _pitch;
	GLfloat _moveSpeed;
	GLfloat _mouseSensitivity;

	Camera();
	void processKeyboard(CameraDirection dir);
	void processMouse(GLfloat x_offset, GLfloat y_offset);
	glm::mat4 getViewMatrix();

private:
	void updateVectors();
};