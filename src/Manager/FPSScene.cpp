#include "FPSScene.hpp"
using namespace Managers;

#include "../Rendering/Camera.hpp"
#include "../Core/Game/SpaceGame/Characters/Ship.hpp"
 
FPSScene::FPSScene()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);  
    glEnable(GL_DEPTH_TEST);
    gameObjectManager = new Game::Managers::ObjectManager();
    actorManager = new Game::Managers::ActorManager();
    shader_manager = new ShaderManager();
    camera = new Camera(glm::vec3(0,5,10), glm::vec3(0,1,0), 0.1, 0.05);
    light = new Light(
        glm::vec3(0,5,0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, 1.0, 1.0),
        1.0,
        0.01,
        0.01
    );
    projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.001f, 10000.0f);
    //models_manager = new ModelsManager();
    shader_manager->CreateProgram("textureShader",
                                    "src/shaders/vertex_shader.glsl",
                                    "src/shaders/fragment_shader.glsl");
    shader_manager->CreateProgram("colorShader",
                                    "src/shaders/vertex_shader_color.glsl",
                                    "src/shaders/fragment_shader_color.glsl");
    shader_manager->CreateProgram("loadedShader",
                                    "src/shaders/vert_obj.glsl",
                                    "src/shaders/frag_obj.glsl");
    shader_manager->CreateProgram("matShader",
                                    "src/shaders/vert_mat_tex.glsl",
                                    "src/shaders/frag_mat_tex.glsl");

    models_manager = new ModelsManager(camera);

    Models::LoadedObject* shipModel = new Models::LoadedObject("src/Models/ship2.obj");
    Models::LoadedObject* laserModel = new Models::LoadedObject("src/Models/laser.obj");
    shipModel->SetLight(light);
    laserModel->SetLight(light);

    Models::Grid* grid = new Models::Grid();

    grid->SetProgram(ShaderManager::GetShader("colorShader"));
    grid->SetProjection(projection);
    grid->SetModelView(camera->getModelView());
    grid->SetCamera(this->camera);
    grid->Create();

    laserModel->SetProgram(ShaderManager::GetShader("matShader"));
    laserModel->SetProjection(projection);
    laserModel->SetModelView(camera->getModelView());
    laserModel->SetCamera(this->camera);
    laserModel->Create();

    models_manager->AddModel("grid", grid);
    //unsigned int texture = textureLoader->LoadTexture("Textures/Crate.bmp", 256, 256);

    //models_manager->AddModel("ship", shipModel);
    camera->setLookAt(glm::vec3(0,-1,-3));
    /* Setting up input */
    Game::Characters::Ship* ship = new Game::Characters::Ship(
        shipModel,
        ShaderManager::GetShader("matShader"),
        projection,
        camera->getModelView(),
        camera
    );
    actorManager->AddActor("player", ship);
    gameObjectManager->AddObject("ship", ship);
    models_manager->AddModel("ship", laserModel);
}
 
FPSScene::~FPSScene()
{
   delete shader_manager;
   delete models_manager;
   delete camera;
}
 
void FPSScene::notifyBeginFrame()
{
    if(keys['w']) {
        camera->processKeyboard(Rendering::Camera::FORWARD, 1);
    }
    if(keys['s']) {
        camera->processKeyboard(Rendering::Camera::BACKWARD, 1);
    }
    if(keys['a']) {
        camera->processKeyboard(Rendering::Camera::LEFT, 1);
    }
    if(keys['d']) {
        camera->processKeyboard(Rendering::Camera::RIGHT, 1);
    }
    models_manager->Update();
    gameObjectManager->Update();
}
 
void FPSScene::notifyDisplayFrame()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    models_manager->Draw();
    gameObjectManager->Update();
}
 
void FPSScene::notifyEndFrame()
{
 //nothing here for the moment
}

void FPSScene::notifyKeyboardUp(unsigned char key) {
    keys[key] = false;
}

void FPSScene::notifyKeyboardInput(unsigned char key) {
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

void FPSScene::notifyMouseInput(int button, int state, int x, int y) {
    //std::cout<< "MOUSE X: " << x << " Y: " << y << std::endl;
}

bool firstMouse = true;
float lastX;
float lastY;

void FPSScene::notifyMouseMovementInput(int x, int y) {
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
 
void FPSScene::notifyReshape(int width,
                                  int height,
                                  int previous_width,
                                  int previous_height)
{
 //nothing here for the moment 
 
}