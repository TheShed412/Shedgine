#pragma once
#include <SDL2/SDL.h>

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
            virtual void MoveForward(int deltaTime) = 0;
            virtual void MoveBackward(int deltaTime)= 0;
            virtual void MoveRight(int deltaTime)= 0;
            virtual void MoveLeft(int deltaTime) = 0;
            virtual void MoveUp(int deltaTime) = 0;
            virtual void MoveDown(int deltaTime) = 0;
            virtual void TurnRight(int deltaTime) = 0;
            virtual void TurnLeft(int deltaTime) = 0;
            virtual void TurnUp(int deltaTime) = 0;
            virtual void TurnDown(int deltaTime) = 0;
            virtual void LookAtObject(glm::vec3) = 0;
            virtual void Action(int deltaTime) = 0;
            virtual void HandleInput(bool[], int) = 0;
            virtual void HandleMouseInput(int,int) = 0;
    };
    inline Actor::~Actor()
    {//blank
    }
} // namespace Game
