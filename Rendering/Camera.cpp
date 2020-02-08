#include "Camera.hpp"

using namespace Rendering;

Camera::Camera(glm::vec3 _position, glm::vec3 _worldUp, GLfloat _mouseSensitivity, GLfloat _movementSpeed) {
    position = _position;
    worldUpVec = _worldUp;
    mouseSensitivity = _mouseSensitivity;
    movementSpeed = _movementSpeed;
    updateVectors();
}

Camera::~Camera() {
}

void Camera::processMouseMovement(float xoffset, float yoffset){

}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {

}

void Camera::updateVectors() {

}