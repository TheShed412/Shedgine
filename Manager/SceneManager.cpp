#include "SceneManager.hpp"
using namespace Managers;
 
SceneManager::SceneManager()
{
  glEnable(GL_DEPTH_TEST);
 
  shader_manager = new ShaderManager();
  shader_manager->CreateProgram("colorShader",
                                "shaders/vertex_shader.glsl",
                                "shaders/fragment_shader.glsl");
}
 
SceneManager::~SceneManager()
{
   delete shader_manager;
}
 
void SceneManager::notifyBeginFrame()
{
    //nothing here for the moment
}
 
void SceneManager::notifyDisplayFrame()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glClearColor(0.0, 0.0, 0.0, 1.0);
 
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