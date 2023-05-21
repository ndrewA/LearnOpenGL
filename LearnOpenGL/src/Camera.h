#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Timer.h"

class Camera
{
public:
	Camera() { }

	enum direction 
	{ 
		front = 1 << 0, 
		back = 1 << 1,
		right = 1 << 2,
		left = 1 << 4
	};

	glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + cameraFront, worldUp); }
	float getFOV() const { return glm::radians(fov); }

	void processMouseMovement(const float xOffset, const float yOffset);
	void processMouseScroll(const float yOffset);
	void processKeyboard(const char directionMask);

public:
	
private:
	const static float MOVEMENT_SPEED;
	const static float SCROLL_SENSITIVITY;
	const static float MOUSE_SENSITIVITY;

private:
	utilities::Timer timer;

	glm::vec3 position		= glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront	= glm::vec3(0.0f, 0.0f,-1.0f);
	glm::vec3 worldUp		= glm::vec3(0.0f, 1.0f, 0.0f);

	float pitch = 0.0f;
	float yaw	= 0.0f;

	float fov = 45.0f;

private:
	void updateCameraRotation();
};

