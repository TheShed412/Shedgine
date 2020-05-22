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
            virtual void MoveForward() = 0;
            virtual void MoveBackward()= 0;
            virtual void MoveRight()= 0;
            virtual void MoveLeft() = 0;
            virtual void MoveUp() = 0;
            virtual void MoveDown() = 0;
            virtual void TurnRight() = 0;
            virtual void TurnLeft() = 0;
            virtual void TurnUp() = 0;
            virtual void TurnDown() = 0;
            virtual void Action() = 0;
    };
    inline Actor::~Actor()
    {//blank
    }
} // namespace Game
