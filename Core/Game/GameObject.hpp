#pragma once

#include "../../Rendering/Models/LoadedObject.hpp"


/**
 * This will be the base game object class
 * 
*/
namespace Game
{
    class GameObject {
        protected:
            Game::GameObject* parent;
            Rendering::Models::LoadedObject* model;
            bool active;
            std::string scene; // TODO: will be a reference to the scene
        
        public:
            virtual ~GameObject() = 0;
            virtual void Destroy() = 0;
            virtual void Update() = 0;
            virtual void Draw() = 0;
            virtual void Create() = 0;
            
    };
    inline GameObject::~GameObject()
    {//blank
    }
} // namespace Game
