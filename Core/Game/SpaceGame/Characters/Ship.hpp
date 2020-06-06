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
                void SetFlightSpeed(float flightSpeed);
                void SetPitch(float max, float delta);
                void SetYaw(float max, float delta);
                void SetRoll(float max, float delta);
        };
    } // namespace Characters
    
} // namespace Game
