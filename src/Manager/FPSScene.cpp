#include "FPSScene.hpp"
using namespace Managers;

#include "../Rendering/Camera.hpp"
#include "../Rendering/Models/LoadedObject.hpp"
#include "../Core/Game/SpaceGame/Characters/Ship.hpp"
#include "../Core/Game/FPS/Characters/Terry.hpp"
#include "../Core/Physics/Debugger/GLDebugDrawer.hpp"
#include "../Core/Init/InitSDL.hpp"

void collisionCheck(btDynamicsWorld *dynamicsWorld, btScalar timeStep) {
    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
}

FPSScene::FPSScene()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);  
    glEnable(GL_DEPTH_TEST);

    sdlWindow = Core::Init::InitSDL::sdlWindow;
    gameObjectManager = new Game::Managers::ObjectManager();
    actorManager = new Game::Managers::ActorManager();
    shader_manager = new ShaderManager();
    debugDrawer = new GLDebugDrawer();
    // TODO: make it so I can control the speed with the player
    camera = new Camera(glm::vec3(10,3,25), glm::vec3(0,1,0), 0.2, 20.0);
    light = new Light(
        glm::vec3(0,10,0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, 1.0, 1.0),
        1.0,
        0.01,
        0.01
    );
    projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.001f, 10000.0f);
    //models_manager = new ModelsManager();
    shader_manager->CreateProgram("n64Shader",
                                    "src/shaders/n64_vert.glsl",
                                    "src/shaders/n64_frag.glsl");
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

    setupCollisions();

    Physics::PhysicsObject* groundModel = new Physics::PhysicsObject(Physics::GROUND, 0.0f, true, 0.4, 1.5,"src/Models/big_floor.obj");

    dynamicsWorld->setGravity(btVector3(0,-15,0));
    dynamicsWorld->setInternalTickCallback(collisionCheck);
    

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            Physics::PhysicsObject* crate = new Physics::PhysicsObject(Physics::DYNAMIC, 5.0f, true, 0.4, 1.5,"src/Models/new_crate.obj");
            addToScene(crate, std::vector<VertexFormat>(), "n64Shader", "crate" + std::to_string(i) + std::to_string(j));
            crate->setPosition(glm::vec3(i*5, 2, (j * 5) + 5));
            crate->setScale(glm::vec3(1));
        }
    }

    addToScene(groundModel, std::vector<VertexFormat>(), "matShader", "ground");
    groundModel->setPosition(glm::vec3(0,0,0));

    //unsigned int texture = textureLoader->LoadTexture("Textures/Crate.bmp", 256, 256);

    
    camera->setLookAt(glm::vec3(0,0.5,-3));

    Game::Characters::Terry* terry = new Game::Characters::Terry(
        NULL,
        ShaderManager::GetShader("matShader"),
        projection,
        camera->getModelView(),
        camera
    );

    /* Setting up input */
    actorManager->AddActor("player", terry);
    inBuffer = false;
    mouseBuffer = 100;

    elapsedTime = 0;
    currentTime = 0;
    previousTime = 0;
}

FPSScene::FPSScene(Core::WindowInfo windowInfo) : FPSScene() {
    this->windowInfo = windowInfo;
}

 
FPSScene::~FPSScene()
{
    for (size_t i = 0; i < collisionShapes.size(); i++)
    {
        delete collisionShapes.at(i);
    }
    

    delete shader_manager;
    delete models_manager;
    delete camera;
    delete dynamicsWorld;
    delete overlappingPairCache;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
}
 
void FPSScene::addToScene(Rendering::Models::LoadedObject* newObject, std::string shaderName, std::string modelName) {

}

void FPSScene::addToScene(Physics::PhysicsObject* newObject, std::vector<VertexFormat> hitBox, std::string shaderName, std::string modelName) {
    newObject->SetLight(light);

    newObject->SetProgram(ShaderManager::GetShader(shaderName));
    newObject->SetProjection(projection);
    newObject->SetModelView(camera->getModelView());
    newObject->SetCamera(this->camera);
    newObject->Create(hitBox);

    models_manager->AddModel(modelName, newObject);
    physicsObjects[modelName] = newObject;

    dynamicsWorld->addRigidBody(newObject->getRigidBody());
    
    collisionShapes.push_back(newObject->getCollisionShape());
}

void FPSScene::addToScene(Game::Actor* newObject, std::vector<VertexFormat> hitBox, std::string shaderName, std::string modelName) {

}

void FPSScene::notifyBeginFrame()
{
    // Do the time shit
    previousTime = currentTime;
    currentTime = SDL_GetTicks();
    elapsedTime = currentTime - previousTime;

    actorManager->GetActor("player").HandleInput(keys, elapsedTime);
    models_manager->Update();
    gameObjectManager->Update();
}
 
void FPSScene::notifyDisplayFrame()
{
    glClearColor(0.53, 0.81, 0.92, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    models_manager->Draw();
    gameObjectManager->Update();

}
 
void FPSScene::notifyEndFrame()
{
    // TODO: need to change this based on frame rate
    for (auto physicsObject : physicsObjects){
        physicsObject.second->updateObjectPosition();
    }
    dynamicsWorld->stepSimulation(btScalar(elapsedTime/1000.0f), 1, btScalar(1.0)/btScalar(60.0));

}

void FPSScene::notifyKeyboardUp(SDL_Keysym key) {
    keys[key.sym] = false;
}

void FPSScene::notifyKeyboardInput(SDL_Keysym key) {
    keys[key.sym] = true;
}

void FPSScene::notifyMouseInput(int button, int state, int x, int y) {

}


void FPSScene::notifyMouseMovementInput(int x, int y) {
    actorManager->GetActor("player").HandleMouseInput(x, -y);

}
 
void FPSScene::notifyReshape(int width,
                                  int height,
                                  int previous_width,
                                  int previous_height)
{
 //nothing here for the moment 
 
}

// Setting up physics stuff here
void FPSScene::setupCollisions() {
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
}