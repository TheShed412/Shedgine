#include "SceneManager.hpp"
#include "../Core/Game/SpaceGame/Characters/Ship.hpp"

using namespace Managers;
 
/*
    SceneManager seems to be more of just a scene object that is consturcted instead of 
    the collection of scenes in a game. I might change this to Scene and make an actual
    scene manager that keeps a list of scenes in a game.

    The scene manager should have a map of scenes with names that can be opned from any other scene.
    Scene loading will be controlled by the scene manager. 
*/
SceneManager::SceneManager()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);  
    glEnable(GL_DEPTH_TEST);
    gameObjectManager = new Game::Managers::ObjectManager();
    actorManager = new Game::Managers::ActorManager();
    shader_manager = new ShaderManager();
    camera = new Camera(glm::vec3(0,15,25), glm::vec3(0,1,0), 0.5, 0.05);
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
    shipModel->SetLight(light);

    // TODO: make grid a game object, or handled somewhere else
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

    // Game::Characters::Redical* redical = new Game::Characters::Redical(
    //     redicalModel,
    //     ShaderManager::GetShader("colorShader"),
    //     projection,
    //     camera->getModelView(),
    //     camera
    // );
    actorManager->AddActor("player", ship);
    gameObjectManager->AddObject("ship", ship);
    // actorManager->AddActor("retical", redical);
    // gameObjectManager->AddObject("retical", redical);
}
 
SceneManager::~SceneManager()
{
   delete shader_manager;
   delete models_manager;
   delete camera;
   delete gameObjectManager;
}
 
void SceneManager::notifyBeginFrame()
{

    // if(keys['w']) {
    //     //camera->processKeyboard(Camera::FORWARD, 1);
    //     actorManager->GetActor("player").TurnUp();
    // }
    // if(keys['s']) {
    //     //camera->processKeyboard(Camera::BACKWARD, 1);
    //     actorManager->GetActor("player").TurnDown();
    // }
    // if(keys['a']) {
    //     //camera->processKeyboard(Camera::LEFT, 1);
    //     actorManager->GetActor("player").TurnLeft();
    // }
    // if(keys['d']) {
    //     //camera->processKeyboard(Camera::RIGHT, 1);
    //     actorManager->GetActor("player").TurnRight();
    // }

    actorManager->GetActor("player").HandleInput(keys);

    models_manager->Update();
    gameObjectManager->Update();
    
}
 
void SceneManager::notifyDisplayFrame()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    models_manager->Draw();
    gameObjectManager->Draw();
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

bool firstMouse1 = true;
float lastX1;
float lastY1;

void SceneManager::notifyMouseMovementInput(int x, int y) {
    if (firstMouse1)
    {
        lastX1 = x;
        lastY1 = y;
        firstMouse1 = false;
    }

    float xoffset = x - lastX1;
    float yoffset = lastY1 - y; // reversed since y-coordinates go from bottom to top

    lastX1 = x;
    lastY1 = y;
    //camera->processMouseMovement(xoffset, yoffset);
}
 
void SceneManager::notifyReshape(int width,
                                  int height,
                                  int previous_width,
                                  int previous_height)
{
 //nothing here for the moment 
 
}