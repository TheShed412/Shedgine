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
                glm::mat4 MoveForward() override;
                glm::mat4 MoveBackward() override;
                glm::mat4 MoveRight() override;
                glm::mat4 MoveLeft() override;
                glm::mat4 MoveUp() override;
                glm::mat4 MoveDown() override;
                glm::mat4 TurnRight() override;
                glm::mat4 TurnLeft() override;
                glm::mat4 TurnUp() override;
                glm::mat4 TurnDown() override;
                void HandleMouseInput(int,int) override;
                void HandleInput(bool[], int);
                void Action() override;
                void LookAtObject(glm::vec3) override;

                glm::vec3 GetCoords();
        };
    } // namespace Characters
    
} // namespace Game
