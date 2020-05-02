#pragma once
#include <map>
#include "ShaderManager.hpp"
#include "../Rendering/IGameObject.hpp"
#include "../Rendering/Models/Triangle.hpp"
#include "../Rendering/Models/Cube.hpp"
#include "../Rendering/Models/LoadedObject.hpp"
#include "../Rendering/Models/Grid.hpp"
#include "../Rendering/Texture/TextureLoader.hpp"
 
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
         void AddModel(const std::string& gameModelName, IGameObject* gameModel);
         void SetCamera(Camera* camera);
         const IGameObject& GetModel(const std::string& gameModelName) const;
 
     private:
        std::map<std::string, IGameObject*> gameModelList;
        Camera* camera;
   };
}