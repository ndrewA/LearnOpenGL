#include "Camera.h"

#include <time.h>

const float Camera::MOVEMENT_SPEED = 2.5f;
const float Camera::SCROLL_SENSITIVITY = 2.5f;
const float Camera::MOUSE_SENSITIVITY = 0.1f;

void Camera::processMouseMovement(const float xOffset, const float yOffset)
{
    yaw     += xOffset * MOUSE_SENSITIVITY;
    pitch   -= yOffset * MOUSE_SENSITIVITY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;
    updateCameraRotation();
}

void Camera::processMouseScroll(const float yOffset)
{
    fov -= (float)yOffset * SCROLL_SENSITIVITY;

    if (fov < 1.0f)
        fov = 1.0f;
    else if (fov > 45.0f)
        fov = 45.0f;
    updateCameraRotation();
}

void Camera::processKeyboard(const char directionMask)
{
    const float speedOnDeltaTime = MOVEMENT_SPEED * timer.getDeltaTime();

    if (directionMask & direction::front)
        position += speedOnDeltaTime * cameraFront;
    if (directionMask & direction::back)
        position -= speedOnDeltaTime * cameraFront;
    if (directionMask & direction::left)
        position -= speedOnDeltaTime * glm::normalize(glm::cross(cameraFront, worldUp));
    if (directionMask & direction::right)
        position += speedOnDeltaTime * glm::normalize(glm::cross(cameraFront, worldUp));
    if (directionMask & (char)0x0)
        timer.resetTimer();
}

void Camera::updateCameraRotation()
{
    glm::vec3 direction
    {
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    };

    cameraFront = glm::normalize(direction);
}