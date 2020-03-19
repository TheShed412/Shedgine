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
    textureLoader = new TextureLoader();
    camera = new Camera(glm::vec3(0,0,2), glm::vec3(0,1,0), 0.5, 0.05);
    //models_manager = new ModelsManager();
    shader_manager->CreateProgram("textureShader",
                                    "shaders/vertex_shader.glsl",
                                    "shaders/fragment_shader.glsl");
    shader_manager->CreateProgram("colorShader",
                                    "shaders/vertex_shader_color.glsl",
                                    "shaders/fragment_shader_color.glsl");
    shader_manager->CreateProgram("loadedShader",
                                    "shaders/vert_obj.glsl",
                                    "shaders/frag_obj.glsl");

    models_manager = new ModelsManager(camera, textureLoader);

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
    if(keys['w']) {
        camera->processKeyboard(FORWARD, 1);
    }
    if(keys['s']) {
        camera->processKeyboard(BACKWARD, 1);
    }
    if(keys['a']) {
        camera->processKeyboard(LEFT, 1);
    }
    if(keys['d']) {
        camera->processKeyboard(RIGHT, 1);
    }
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

void SceneManager::notifyKeyboardUp(unsigned char key) {
    keys[key] = false;
}

void SceneManager::notifyKeyboardInput(unsigned char key) {
    // if(key == 'w') {
    //     camera->processKeyboard(FORWARD, 1);
    // }
    // if(key == 's') {
    //     camera->processKeyboard(BACKWARD, 1);
    // }
    // if(key == 'a') {
    //     camera->processKeyboard(LEFT, 1);
    // }
    // if(key == 'd') {
    //     camera->processKeyboard(RIGHT, 1);
    // }
    keys[key] = true;
}

void SceneManager::notifyMouseInput(int button, int state, int x, int y) {
    //std::cout<< "MOUSE X: " << x << " Y: " << y << std::endl;
}

bool firstMouse = true;
float lastX;
float lastY;

void SceneManager::notifyMouseMovementInput(int x, int y) {
    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y; // reversed since y-coordinates go from bottom to top

    lastX = x;
    lastY = y;
    camera->processMouseMovement(xoffset, yoffset);
}
 
void SceneManager::notifyReshape(int width,
                                  int height,
                                  int previous_width,
                                  int previous_height)
{
 //nothing here for the moment 
 
}