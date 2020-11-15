#include "ObjectManager.hpp"

using namespace Game;
using namespace Game::Managers;

ObjectManager::ObjectManager(){}

ObjectManager::~ObjectManager()
{
    //auto -it's a map iterator
    for (auto model: gameObjectList)
    {
      delete model.second;
    }
    gameObjectList.clear();
}
 
void ObjectManager::DeleteObject(const std::string& gameObjectName)
{
  GameObject* model = gameObjectList[gameObjectName];
  model->Destroy();
  gameObjectList.erase(gameObjectName);
}

void ObjectManager::AddObject(const std::string& gameObjectName, GameObject* gameObject)
{
  gameObjectList[gameObjectName] = gameObject;
}
 
GameObject& ObjectManager::GetObject(const std::string& gameObjectName) const
{
  return (*gameObjectList.at(gameObjectName));
}
 
void ObjectManager::Update()
{
   //auto -it's a map iterator
  for (auto object: gameObjectList)
  {
    object.second->Update();
  }
}
 
void ObjectManager::Draw()
{
   //auto -it's a map iterator
   for (auto model : gameObjectList)
   {
      model.second->Draw();
   }
}