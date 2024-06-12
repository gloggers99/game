//
// Created by lucas on 6/12/24.
//

#ifndef GAME_CAMERA_HPP
#define GAME_CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>
#include "../Window.hpp"

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    bool firstMouse = true;
    float yaw   = -90.0f;
    float pitch =  0.0f;
    float lastX =  800.0f / 2.0;
    float lastY =  600.0 / 2.0;
    float fov   =  90.0f;
public:
    glm::mat4 getMatrix();
    void move(Direction direction = Direction::FORWARD, float speed = 2.5f);
    void handleMouse(Window *window);

    Camera();
    ~Camera();
};


#endif //GAME_CAMERA_HPP
