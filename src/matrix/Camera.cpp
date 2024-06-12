//
// Created by lucas on 6/12/24.
//

#include <glm/ext/matrix_transform.hpp>

#include <stdexcept>
#include <cmath>
#include <iostream>

#include "Camera.hpp"

glm::mat4 Camera::getMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::move(Direction direction, float speed) {
    switch (direction) {
        case Direction::FORWARD:
            this->cameraPos += cameraFront * speed;
            break;
        case Direction::BACKWARD:
            this->cameraPos -= cameraFront * speed;
            break;
        case Direction::LEFT:
            this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * speed;
            break;
        case Direction::RIGHT:
            this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * speed;
            break;
        default:
            throw std::runtime_error("invalid direction provided.");
    }
}

void Camera::handleMouse(Window *window) {
    double xpos, ypos;
    glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
    std::cout << xpos << " " << ypos << "\n";

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front.y = std::sin(glm::radians(pitch));
    front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

Camera::Camera() {
    this->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera() = default;
