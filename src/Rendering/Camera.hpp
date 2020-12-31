#pragma once
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
            Camera(glm::vec3 _position, glm::vec3 _worldUp, float _mouseSensitivity, float _movementSpeed, int windowHeight, int wndowWidth);
            void processMouseMovement(float xoffset, float yoffset);
            void processKeyboard(CameraMovement direction, float deltaTime);
            void setLookAt(glm::vec3 target);
            void addToPosition(glm::vec3 diff);
            glm::mat4 getModelView();
            void setProgram(unsigned int program);
            void getPickRays(float pickDistance, glm::vec3* outStart, glm::vec3* outEnd);
            void setProjection(glm::mat4);
            glm::mat4 getProjection();
            glm::vec3 getPosition();
            glm::vec3 getLookDirection();

        private:
            glm::vec3 position;// current location, WASD
            glm::vec3 lookDirection;// where you are looking at, mouse
            glm::vec3 rightVec;// = {0, 1, 0};
            glm::vec3 upVec;// calculated with look direction and rightVec
            glm::vec3 worldUpVec;
            glm::mat4 projection;
            float movementSpeed;
            float mouseSensitivity;
            float yaw;
            float pitch;
            int windowHeight;
            int windowWidth;
            unsigned int program;
            void updateVectors();
    };

}