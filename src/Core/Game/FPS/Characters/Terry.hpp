#pragma once
#include "../../Actor.hpp"
#include "../../../../Rendering/Models/LoadedObject.hpp"


namespace Game
{
    namespace Characters
    {
        class Terry : virtual public Actor
        {
            private:
                Rendering::Camera* camera;
                bool moveForward = false;
                bool moveBack = false;
                bool moveLeft = false;
                bool moveRight = false;
                bool leftPressed = false;
                bool rightpressed = false;
            public:
                Terry();
                Terry(Rendering::Models::LoadedObject*,
                        GLuint,
                        glm::mat4,
                        glm::mat4,
                        Rendering::Camera*);
                ~Terry();
                void Update() override;
                void Draw() override;
                void Create() override;
                void Destroy() override;
                void MoveForward(bool) override;
                void MoveBackward(bool) override;
                void MoveRight(bool) override;
                void MoveLeft(bool) override;
                void MoveUp(int deltaTime) override;
                void MoveDown(int deltaTime) override;
                void TurnRight(int deltaTime) override;
                void TurnLeft(int deltaTime) override;
                void TurnUp(int deltaTime) override;
                void TurnDown(int deltaTime) override;
                void HandleMouseInput(int,int) override;
                void HandleLeftMouse(bool) override;
                void HandleRightMouse(bool) override;
                void HandleInput(int deltaTime);
                void Action(int deltaTime) override;
                void LookAtObject(glm::vec3) override;

                glm::vec3 GetCoords();
        };
    } // namespace Characters
    
} // namespace Game
