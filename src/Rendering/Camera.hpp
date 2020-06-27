#pragma once
#include <GL/glut.h>
#include "glm/gtc/matrix_transform.hpp"

namespace Rendering {

    class Camera {

        public:
            enum CameraMovement {
                FORWARD,
                BACKWARD,
                LEFT,
                RIGHT,
                BUTTON_UP,
                BUTTON_DOWN
            };
            Camera();
            ~Camera();
            Camera(glm::vec3 _position, glm::vec3 _worldUp, GLfloat _mouseSensitivity, GLfloat _movementSpeed);
            void processMouseMovement(float xoffset, float yoffset);
            void processKeyboard(CameraMovement direction, float deltaTime);
            void setLookAt(glm::vec3 target);
            void addToPosition(glm::vec3 diff);
            glm::mat4 getModelView();
            void setProgram(GLuint program);

        private:
            glm::vec3 position;// current location, WASD
            glm::vec3 lookDirection;// where you are looking at, mouse
            glm::vec3 rightVec;// = {0, 1, 0};
            glm::vec3 upVec;// calculated with look direction and rightVec
            glm::vec3 worldUpVec;
            GLfloat movementSpeed;
            GLfloat mouseSensitivity;
            GLfloat yaw;
            GLfloat pitch;
            GLuint program;
            void updateVectors();
    };

}