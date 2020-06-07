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
                void MoveForward() override;
                void MoveBackward() override;
                void MoveRight() override;
                void MoveLeft() override;
                void MoveUp() override;
                void MoveDown() override;
                void TurnRight() override;
                void TurnLeft() override;
                void TurnUp() override;
                void TurnDown() override;
                void Action() override;
        };
    } // namespace Characters
    
} // namespace Game
