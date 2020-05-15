#include "SceneManager.hpp"
using namespace Managers;
 
/*
    SceneManager seems to be more of just a scene object that is consturcted instead of 
    the collection of scenes in a game. I might change this to Scene and make an actual
    scene manager that keeps a list of scenes in a game
*/
SceneManager::SceneManager()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);  
    glEnable(GL_DEPTH_TEST);
    shader_manager = new ShaderManager();
    camera = new Camera(glm::vec3(0,4,10), glm::vec3(0,1,0), 0.5, 0.05);
    projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.001f, 10000.0f);
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

    models_manager = new ModelsManager(camera);

    Models::LoadedObject* shipModel = new Models::LoadedObject("Models/SmallSpaceFighter.obj");

    #ifdef _DEBUG
    Models::Grid* grid = new Models::Grid();

    grid->SetProgram(ShaderManager::GetShader("colorShader"));
    grid->SetProjection(projection);
    grid->SetModelView(camera->getModelView());
    grid->SetCamera(this->camera);
    grid->Create();

    models_manager->AddModel("grid", grid);
    #endif
    //unsigned int texture = textureLoader->LoadTexture("Textures/Crate.bmp", 256, 256);

    shipModel->SetProgram(ShaderManager::GetShader("colorShader"));
    shipModel->SetProjection(projection);
    shipModel->SetModelView(camera->getModelView());
    shipModel->SetCamera(this->camera);
    shipModel->Create();

    models_manager->AddModel("ship", shipModel);
    camera->setLookAt(glm::vec3(0,-1,-3));
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
        //camera->processKeyboard(Camera::FORWARD, 1);
        models_manager->GetModel("ship").processKeyboard(FORWARD, 1);
    }
    if(keys['s']) {
        //camera->processKeyboard(Camera::BACKWARD, 1);
        models_manager->GetModel("ship").processKeyboard(BACKWARD, 1);
    }
    if(keys['a']) {
        //camera->processKeyboard(Camera::LEFT, 1);
        models_manager->GetModel("ship").processKeyboard(LEFT, 1);
    }
    if(keys['d']) {
        //camera->processKeyboard(Camera::RIGHT, 1);
        models_manager->GetModel("ship").processKeyboard(RIGHT, 1);
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
    //camera->processMouseMovement(xoffset, yoffset);
}
 
void SceneManager::notifyReshape(int width,
                                  int height,
                                  int previous_width,
                                  int previous_height)
{
 //nothing here for the moment 
 
}