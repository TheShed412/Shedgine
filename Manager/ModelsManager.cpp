#include "ModelsManager.hpp"
#include "../Rendering/Camera.hpp"
 
using namespace Managers;
using namespace Rendering;

ModelsManager::ModelsManager(){}
 
ModelsManager::ModelsManager(Camera* camera)
{
    this->camera = camera;
    GLuint program = ShaderManager::GetShader("colorShader");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.001f, 10000.0f);
    Models::Cube* cube = new Models::Cube();
    Models::Grid* grid = new Models::Grid();

    cube->SetProgram(program);
    cube->SetProjection(projection);
    cube->SetModelView(camera->getModelView());// probably can replace all of this with the camera reference
    cube->SetCamera(this->camera);
    cube->Create();

    grid->SetProgram(program);
    grid->SetProjection(projection);
    grid->SetModelView(camera->getModelView());// probably can replace all of this with the camera reference
    grid->SetCamera(this->camera);
    grid->Create();

    gameModelList["cube"] = cube;
    gameModelList["grid"] = grid;
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
 
const IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
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