#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

using namespace Rendering;

Camera::Camera() {}

Camera::Camera(glm::vec3 _position, glm::vec3 _worldUp, float _mouseSensitivity, float _movementSpeed, int windowHeight, int windowWidth) {
    position = _position;
    worldUpVec = _worldUp;
    mouseSensitivity = _mouseSensitivity;
    movementSpeed = _movementSpeed;
    pitch = 0.0f;
    yaw = -90.0f;
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
    updateVectors();
}

void Camera::setProgram(unsigned int program) {
    this->program = program;
}

Camera::~Camera() {
    // idk what goes here yet lol 
}

glm::mat4 Camera::getModelView() {
    glm::mat4 modelView = glm::lookAt(position, position + lookDirection, upVec);
    return modelView;
}

void Camera::setLookAt(glm::vec3 target) {
    glm::vec3 upVecTmp = glm::cross(rightVec, target);

    // this should throw an error
    if (glm::length(upVecTmp) < 0.00001 * 0.00001) {
        throw "Vector error: up is a zero vector";
    } else {
        upVec = glm::normalize(upVecTmp);
    }

    lookDirection = target;
}

void Camera::addToPosition(glm::vec3 diff) {
    position += diff;
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

    switch(direction) {
        case FORWARD:
            position += glm::cross(glm::vec3(0,1.0,0), rightVec) * velocity;
        break;
        case BACKWARD:
            position -= glm::cross(glm::vec3(0,1.0,0), rightVec) * velocity;
        break;
        case LEFT:
            position -= rightVec * velocity;
        break;
        case RIGHT:
            position += rightVec * velocity;
        break;
    }
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

glm::vec3 Camera::getPickRay(int x, int y) {
    // They are coming in as screen coords
    float xNorm = ((2.0 * x) / windowWidth) - 1.0;
    float yNorm = 1.0 - ((2.0 * y) / windowHeight);
    glm::vec4 rayClip = glm::vec4(xNorm, yNorm, -1.0, 1.0);

    glm::vec4 rayEyeSpace = glm::inverse(this->projection) * rayClip;
    rayEyeSpace = glm::vec4(rayEyeSpace.x, rayEyeSpace.y, -1.0, 0.0);
    glm::vec4 tmpInverse = glm::inverse(this->getModelView()) * rayEyeSpace;
    glm::vec3 rayWorld = glm::normalize(glm::vec3(tmpInverse.x, tmpInverse.y, tmpInverse.z));

    return rayWorld;
    // glm::vec3 coord;
    // coord.x = ((2.0f * x) / this->windowWidth) - 1;
    // coord.y = (((2.0f * x) / this->windowHeight) - 1) * -1;
    // coord.z = 1.0f;

    // coord.x /= this->projection[0].x;
    // coord.x /= this->projection[1].y;

    // glm::mat4 invertedModel = glm::inverse(this->getModelView());

    // float normalized = invertedModel[0].x * coord.x + invertedModel[0].y * coord.y + invertedModel[0].z * coord.z;
}

void Camera::setProjection(glm::mat4 projection) {
    this->projection = projection;
}

glm::mat4 Camera::getProjection() {
    return this->projection;
}

glm::vec3 Camera::getPosition() {
    return this->position;
}

glm::vec3 Camera::getLookDirection() {
    return this->lookDirection;
}