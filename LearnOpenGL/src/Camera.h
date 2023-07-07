#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Timer.h"

enum direction
{
	front = 1 << 0,
	back = 1 << 1,
	right = 1 << 2,
	left = 1 << 4,

	up = 1 << 5,
	down = 1 << 6
};

class Camera
{
public:
	Camera() : position({ 0.f, 0.f, 0.f }) { updateCameraRotation(); }
	Camera(glm::vec3 position) : position(position) { updateCameraRotation(); }

	glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + cameraFront, worldUp); }
	float getFOV() const { return glm::radians(fov); }
	glm::vec3 getPosition() const { return position; }
	glm::vec3 getFront() const { return cameraFront; }

	void processMouseMovement(const float xOffset, const float yOffset);
	void processMouseScroll(const float yOffset);
	void processKeyboard(const char directionMask);

public:

private:
	const static float MOVEMENT_SPEED;
	const static float SCROLL_SENSITIVITY;
	const static float MOUSE_SENSITIVITY;

private:
	Timer timer;

	glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);

	glm::vec3 cameraFront = glm::vec3(0.f, 0.f, -1.f);
	glm::vec3 cameraRight = glm::vec3(1.f, 0.f, 0.f);

	float pitch = 0.f;
	float yaw = 0.f;

	float fov = 45.f;

private:
	void updateCameraRotation();
};