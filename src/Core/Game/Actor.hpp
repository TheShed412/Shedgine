#pragma once
#include "GameObject.hpp"


/**
 * This is the base object for all movable characters/entities
 * 
 * This will inherit from a physics based actor once that is implemented
 * 
*/
namespace Game
{
    class Actor : virtual public GameObject
    {
        public:
            virtual ~Actor() = 0;
            virtual glm::mat4 MoveForward() = 0;
            virtual glm::mat4 MoveBackward()= 0;
            virtual glm::mat4 MoveRight()= 0;
            virtual glm::mat4 MoveLeft() = 0;
            virtual glm::mat4 MoveUp() = 0;
            virtual glm::mat4 MoveDown() = 0;
            virtual glm::mat4 TurnRight() = 0;
            virtual glm::mat4 TurnLeft() = 0;
            virtual glm::mat4 TurnUp() = 0;
            virtual glm::mat4 TurnDown() = 0;
            virtual void LookAtObject(glm::vec3) = 0;
            virtual void Action() = 0;
            virtual void HandleInput(unsigned char[]) = 0;
            virtual void HandleMouseInput(int,int) = 0;
    };
    inline Actor::~Actor()
    {//blank
    }
} // namespace Game
