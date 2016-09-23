#include "Camera.h"

// Default constructor
Camera::Camera()
{
	_yaw = YAW;
	_pitch = PITCH;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);
	_moveSpeed = MOVE_SPEED;
	_mouseSensitivity = MOUSE_SENS;
}

void Camera::processKeyboard(CameraDirection dir)
{
	switch (dir)
	{
	case CameraDirection::FORWARD:
		_pos += _front * _moveSpeed;
		break;
	case CameraDirection::BACKWARD:
		_pos -= _front * _moveSpeed;
		break;
	case CameraDirection::LEFT:
		_pos -= glm::normalize(glm::cross(_front, _up)) * _moveSpeed;
		break;
	case CameraDirection::RIGHT:
		_pos += glm::normalize(glm::cross(_front, _up)) *  _moveSpeed;
		break;
	}
}

void Camera::processMouse(GLfloat x_offset, GLfloat y_offset)
{
	x_offset *= _mouseSensitivity;
	y_offset *= _mouseSensitivity;

	_yaw += x_offset;
	_pitch += y_offset;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	updateVectors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(_pos, _pos + _front, _up);
}

void Camera::updateVectors()
{
	glm::vec3 front;
	front.x = glm::cos(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
	front.y = glm::sin(glm::radians(_pitch));
	front.z = glm::sin(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
	_front = glm::normalize(front);
}
