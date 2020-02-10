#pragma once
#include <map>
#include "ShaderManager.hpp"
#include "../Rendering/IGameObject.hpp"
#include "../Rendering/Models/Triangle.hpp"
#include "../Rendering/Models/Cube.hpp"
 
using namespace Rendering;
namespace Managers
{
  class ModelsManager
   {
     public:
         ModelsManager();
         ModelsManager(Camera* camera);
        ~ModelsManager();
 
         void Draw();
         void Update();
         void DeleteModel(const std::string& gameModelName);
         void SetCamera(Camera* camera);
         const IGameObject& GetModel(const std::string& gameModelName) const;
 
     private:
        std::map<std::string, IGameObject*> gameModelList;
        Camera* camera;
   };
}