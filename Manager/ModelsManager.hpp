#pragma once
#include <map>
#include "ShaderManager.hpp"
#include "../Rendering/IGameObject.hpp"
#include "../Rendering/Models/Triangle.hpp"
 
using namespace Rendering;
namespace Managers
{
  class ModelsManager
   {
     public:
         ModelsManager();
        ~ModelsManager();
 
         void Draw();
         void Update();
         void DeleteModel(const std::string& gameModelName);
         const IGameObject& GetModel(const std::string& gameModelName) const;
 
     private:
        std::map<std::string, IGameObject*> gameModelList;
   };
}