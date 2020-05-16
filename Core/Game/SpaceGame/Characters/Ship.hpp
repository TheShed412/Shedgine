#pragma once
#include "../../Actor.hpp"
#include "../../../../Rendering/Models/LoadedObject.hpp"


namespace Game
{
    namespace Characters
    {
        class Ship : public Actor
        {
            private:
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
                void Update();
                void Draw();
                void Create();
                void MoveForward();
                void MoveBackward();
                void MoveRight();
                void MoveLeft();
                void MoveUp();
                void MoveDown();
                void TurnRight();
                void TurnLeft();
                void TurnUp();
                void TurnDown();
                void Action();
                void SetFlightSpeed(float flightSpeed);
                void SetPitch(float max, float delta);
                void SetYaw(float max, float delta);
                void SetRoll(float max, float delta);
        };
    } // namespace Characters
    
} // namespace Game
