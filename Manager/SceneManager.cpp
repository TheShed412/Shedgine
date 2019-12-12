#include "SceneManager.hpp"
using namespace Managers;
 
SceneManager::SceneManager()
{
    glEnable(GL_DEPTH_TEST);
    shader_manager = new ShaderManager();
    models_manager = new ModelsManager();
    shader_manager->CreateProgram("colorShader",
                                    "shaders/vertex_shader.glsl",
                                    "shaders/fragment_shader.glsl");
    glClearColor(1.0, 0.0, 0.0, 1.0);
}
 
SceneManager::~SceneManager()
{
   delete shader_manager;
   delete models_manager;
}
 
void SceneManager::notifyBeginFrame()
{
    models_manager->Update();
}
 
void SceneManager::notifyDisplayFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    models_manager->Draw();
}
 
void SceneManager::notifyEndFrame()
{
 //nothing here for the moment
}
 
void SceneManager::notifyReshape(int width,
                                  int height,
                                  int previous_width,
                                  int previous_height)
{
 //nothing here for the moment 
 
}