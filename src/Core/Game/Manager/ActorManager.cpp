#include "ActorManager.hpp"

using namespace Game;
using namespace Managers;

ActorManager::ActorManager(){}

ActorManager::~ActorManager()
{
    //auto -it's a map iterator
    for (auto model: actorList)
    {
      delete model.second;
    }
    actorList.clear();
}
 
void ActorManager::DeleteActor(const std::string& gameObjectName)
{
  Actor* model = actorList[gameObjectName];
  model->Destroy();
  actorList.erase(gameObjectName);
}

void ActorManager::AddActor(const std::string& gameObjectName, Actor* gameObject)
{
  actorList[gameObjectName] = gameObject;
}
 
Actor& ActorManager::GetActor(const std::string& gameObjectName) const
{
  return (*actorList.at(gameObjectName));
}
 
void ActorManager::Update()
{
   //auto -it's a map iterator
  for (auto object: actorList)
  {
    object.second->Update();
  }
}
 
void ActorManager::Draw()
{
   //auto -it's a map iterator
   for (auto model : actorList)
   {
      model.second->Draw();
   }
}