#include "ModelsManager.hpp"
#include "../Rendering/Camera.hpp"
 
using namespace Graphics::Managers;
using namespace Rendering;

ModelsManager::ModelsManager(){}

/*
  TODO: I need to pull the math of multiplying vertices here, and not in the shaders
*/ 
ModelsManager::ModelsManager(Camera* camera)
{
    this->camera = camera;
}
 
ModelsManager::~ModelsManager()
{
    //auto -it's a map iterator
    for (auto model: gameModelList)
    {
      delete model.second;
    }
    gameModelList.clear();
}
 
void ModelsManager::DeleteModel(const std::string& gameModelName)
{
  IGameObject* model = gameModelList[gameModelName];
  model->Destroy();
  gameModelList.erase(gameModelName);
}

void ModelsManager::AddModel(const std::string& gameModelName, IGameObject* gameModel)
{
  gameModelList[gameModelName] = gameModel;
}
 
IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
  return (*gameModelList.at(gameModelName));
}
 
void ModelsManager::Update()
{
   //auto -it's a map iterator
  for (auto model: gameModelList)
  {
    model.second->Update();
  }
}

void ModelsManager::SetCamera(Camera* camera) {
    this->camera = camera;
}
 
void ModelsManager::Draw()
{
   //auto -it's a map iterator
   for (auto model : gameModelList)
   {
      model.second->Draw();
   }
}