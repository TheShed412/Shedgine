#include "ModelsManager.hpp"
#include "../Rendering/Camera.hpp"
 
using namespace Managers;
using namespace Rendering;

ModelsManager::ModelsManager(){}

/*
  TODO: I need to pull the math of multiplying vertices here, and not in the shaders
*/ 
ModelsManager::ModelsManager(Camera* camera, TextureLoader* textureLoader)
{
    this->camera = camera;
    GLuint program = ShaderManager::GetShader("colorShader");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.001f, 10000.0f);
    Models::Cube* cube = new Models::Cube();
    Models::Grid* grid = new Models::Grid();
    unsigned int texture = textureLoader->LoadTexture("Textures/Crate.bmp", 256, 256);

    cube->SetProgram(program);
    cube->SetProjection(projection);
    cube->SetModelView(camera->getModelView());
    cube->SetCamera(this->camera);
    cube->SetTexture("Create", texture);
    cube->Create();

    // TODO: make this a debug feature at compile time
    grid->SetProgram(program);
    grid->SetProjection(projection);
    grid->SetModelView(camera->getModelView());
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