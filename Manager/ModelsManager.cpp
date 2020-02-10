#include "ModelsManager.hpp"
#include "../Rendering/Camera.hpp"
 
using namespace Managers;
using namespace Rendering;
 
ModelsManager::ModelsManager()
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
    glm::vec3 eyes = {0, 1, -1.5};// starting point {-10, 11, -10, 1}
    glm::vec3 look_at_pos = {0, 0, 0};// starting point {0, 11, -10, 1}
    glm::vec3 up_vec = {0, 1, 0};

    camera = Camera(eyes, up_vec, 1, 1);
    GLuint program = ShaderManager::GetShader("colorShader");
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.001f, 10000.0f);
    Models::Cube* cube = new Models::Cube();
    cube->SetProgram(program);
    cube->SetProjection(projection);
    cube->SetModelView(camera.getModelView());
    cube->SetCamera(&camera);
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
 
void ModelsManager::Draw()
{
   //auto -it's a map iterator
   for (auto model : gameModelList)
   {
      model.second->Draw();
   }
}