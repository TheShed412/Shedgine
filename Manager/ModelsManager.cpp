#include "ModelsManager.hpp"
#include "../Rendering/Camera.hpp"
 
using namespace Managers;
using namespace Rendering;

ModelsManager::ModelsManager(){}
 
ModelsManager::ModelsManager(Camera* camera)
{
 //triangle game object
  // Models::Triangle* triangle = new Models::Triangle();
  // triangle->SetProgram(ShaderManager::GetShader("colorShader"));
  // triangle->Create();
  // gameModelList["triangle"] = triangle;

  // Models::Torus* torus = new Models::Torus();
  // torus->SetProgram(ShaderManager::GetShader("colorShader"));
  // torus->Create();
  // gameModelList["torus"] = torus;
    this->camera = camera;
    GLuint program = ShaderManager::GetShader("colorShader");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.001f, 10000.0f);
    Models::Cube* cube = new Models::Cube();
    cube->SetProgram(program);
    cube->SetProjection(projection);
    cube->SetModelView(camera->getModelView());// probably can replace all of this with the camera reference
    cube->SetCamera(this->camera);
    cube->Create();
    gameModelList["cube"] = cube;
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