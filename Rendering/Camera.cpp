#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

using namespace Rendering;

Camera::Camera() {}

Camera::Camera(glm::vec3 _position, glm::vec3 _worldUp, GLfloat _mouseSensitivity, GLfloat _movementSpeed) {
    position = _position;
    worldUpVec = _worldUp;
    mouseSensitivity = _mouseSensitivity;
    movementSpeed = _movementSpeed;
    pitch = 0.0f;
    yaw = -90.0f;
    updateVectors();
}

void Camera::setProgram(GLuint program) {
    this->program = program;
}

Camera::~Camera() {
    // idk what goes here yet lol 
}

glm::mat4 Camera::getModelView() {
    return glm::lookAt(position, lookDirection, upVec);
}

void Camera::processMouseMovement(float xoffset, float yoffset){
    // TODO: probably using the leran opengl implementation
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateVectors();
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    // TODO: probably using the leran opengl implementation
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += lookDirection * velocity;
    if (direction == BACKWARD)
        position -= lookDirection * velocity;
    if (direction == LEFT)
        position -= rightVec * velocity;
    if (direction == RIGHT)
        position += rightVec * velocity;
    updateVectors();
}

void Camera::updateVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    lookDirection = glm::normalize(front);
    //lookDirection = glm::normalize(position - glm::vec3(0,0,0));// temp for testing
    glm::vec3 rightVecTmp = glm::cross(lookDirection, worldUpVec);  

    // if it's 0, throw error
    if (glm::length(rightVecTmp) < 0.00001 * 0.00001) {
        throw "Vector error: right vector is a zero vector";
    } else {
        rightVec = glm::normalize(rightVecTmp);
    }

    glm::vec3 upVecTmp = glm::cross(rightVec, lookDirection);

    // this should throw an error
    if (glm::length(upVecTmp) < 0.00001 * 0.00001) {
        throw "Vector error: up is a zero vector";
    } else {
        upVec = glm::normalize(upVecTmp);
    }
}