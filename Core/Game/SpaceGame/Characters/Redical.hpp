#pragma once
#include "../../Actor.hpp"
#include "../../../../Rendering/Models/LoadedObject.hpp"
#include "../../../../Rendering/Models/Redical.hpp"


namespace Game
{
    namespace Characters
    {
        class Redical : virtual public Actor
        {
            
            public:
                Redical();
                Redical(Rendering::Models::LoadedObject*,
                        GLuint,
                        glm::mat4,
                        glm::mat4,
                        Rendering::Camera*);
                Redical(Rendering::Models::Redical*,
                        GLuint,
                        glm::mat4,
                        glm::mat4,
                        Rendering::Camera*);
                ~Redical();
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
                void HandleInput(unsigned char[]);
                void Action() override;
        };
    } // namespace Characters
    
} // namespace Game
