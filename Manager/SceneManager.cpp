#include "SceneManager.hpp"
using namespace Managers;
 
/*
    TODO: maybe put the projection and camera in here since those
    make sense to be part of the scene and not models

    Though, I guess I will just be passing them from here to the model manager
    but I do want to be able to control the camera easier

    For the projection matrix, it might be done in the camera later since
    that makes sense to me
*/
SceneManager::SceneManager()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);  
    glEnable(GL_DEPTH_TEST);
    shader_manager = new ShaderManager();
    camera = new Camera(glm::vec3(0,1,1.5), glm::vec3(0,1,0), 1, 1);
    //models_manager = new ModelsManager();
    shader_manager->CreateProgram("colorShader",
                                    "shaders/vertex_shader.glsl",
                                    "shaders/fragment_shader.glsl");
    models_manager = new ModelsManager(camera);

    /* Setting up input */
}
 
SceneManager::~SceneManager()
{
   delete shader_manager;
   delete models_manager;
   delete camera;
}
 
void SceneManager::notifyBeginFrame()
{
    models_manager->Update();
}
 
void SceneManager::notifyDisplayFrame()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    models_manager->Draw();
}
 
void SceneManager::notifyEndFrame()
{
 //nothing here for the moment
}

void SceneManager::notifyKeyboardInput(unsigned char key) {
    if(key == 'w') {
        camera->processKeyboard(FORWARD, 1);
    }
    if(key == 's') {
        camera->processKeyboard(BACKWARD, 1);
    }
    if(key == 'a') {
        camera->processKeyboard(LEFT, 1);
    }
    if(key == 'd') {
        camera->processKeyboard(RIGHT, 1);
    }
}

void SceneManager::notifyMouseInput(float x, float y) {
    std::cout<< "MOUSE X: " << x << " Y: " << y << std::endl;
}
 
void SceneManager::notifyReshape(int width,
                                  int height,
                                  int previous_width,
                                  int previous_height)
{
 //nothing here for the moment 
 
}