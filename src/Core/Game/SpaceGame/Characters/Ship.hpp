#pragma once
#include "../../Actor.hpp"
#include "../../../../Rendering/Models/LoadedObject.hpp"


namespace Game
{
    namespace Characters
    {
        class Ship : virtual public Actor
        {
            private:
                float currentYaw;
                float currentPitch;
                float flightSpeed;
                float maxPitch;
                float pitchDelta; // This is how much the pitch will change, as it gets closer to max, it goes slower
                float maxYaw;
                float yawDelta; // This is how much the yaw will change, as it gets closer to max, it goes slower
                float maxRoll;
                float rollDelta; // This is how much the roll will change, as it gets closer to max, it goes slower
            
            public:
                Ship();
                Ship(Rendering::Models::LoadedObject*,
                        GLuint,
                        glm::mat4,
                        glm::mat4,
                        Rendering::Camera*);
                ~Ship();
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
                void HandleInput(unsigned char[], int);
                void HandleMouseInput(int,int) override;
                void Action() override;
                void LookAtObject(glm::vec3) override;
                void SetFlightSpeed(float flightSpeed);
                void SetPitch(float max, float delta);
                void SetYaw(float max, float delta);
                void SetRoll(float max, float delta);
                glm::vec3 GetCoords();
        };
    } // namespace Characters
    
} // namespace Game
