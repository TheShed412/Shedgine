#include "FPSScene.hpp"
using namespace Graphics::Managers;
using namespace Game::Managers;

#include "../Rendering/Camera.hpp"
#include "../Rendering/Models/LoadedObject.hpp"
#include "../Core/Game/SpaceGame/Characters/Ship.hpp"
#include "../Core/Game/FPS/Characters/Terry.hpp"
#include "../Core/Game/FPS/Crosshairs/OpenGL/SimpleCross.hpp"
#include "../Core/Game/Commands/Command.hpp"
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

    inputHandler = new Input::InputHandler();

    inputHandler->bindW(new Commands::ForwardCommand());
    inputHandler->bindA(new Commands::LeftCommand());
    inputHandler->bindS(new Commands::BackwardCommand());
    inputHandler->bindD(new Commands::RightCommand());

    textureManager = new Managers::TextureManager();
    sdlWindow = Core::Init::InitSDL::sdlWindow;
    gameObjectManager = new Game::Managers::ObjectManager();
    actorManager = new Game::Managers::ActorManager();
    shader_manager = new ShaderManager();
    debugDrawer = new GLDebugDrawer();
    // TODO: make it so I can control the speed with the player
    camera = new Camera(glm::vec3(10,3,25), glm::vec3(0,1,0), 0.2, 20.0, windowInfo.height, windowInfo.width);
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
    this->camera->setProjection(projection);
    //models_manager = new ModelsManager();
    shader_manager->CreateProgram("n64Shader",
                                    "src/shaders/n64_vert.glsl",
                                    "src/shaders/n64_frag.glsl");
    shader_manager->CreateProgram("matShader",
                                    "src/shaders/vert_mat_tex.glsl",
                                    "src/shaders/frag_mat_tex.glsl");
    shader_manager->CreateProgram("chShader",
                                    "src/shaders/crosshair_vert.glsl",
                                    "src/shaders/crosshair_frag.glsl");

    models_manager = new ModelsManager(camera);

    setupCollisions();

    Physics::PhysicsObject* groundModel = new Physics::PhysicsObject(Physics::GROUND, 0.0f, true, 0.4, 1.5,"src/Models/big_floor.obj");

    dynamicsWorld->setGravity(btVector3(0,-15,0));
    dynamicsWorld->setInternalTickCallback(collisionCheck);
    

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 1; j++) {
            Physics::PhysicsObject* crate = new Physics::PhysicsObject(Physics::DYNAMIC, 5.0f, true, 0.4, 1.5,"src/Models/new_crate.obj");
            addToScene(crate, std::vector<VertexFormat>(), "n64Shader", "crate" + std::to_string(i) + std::to_string(j));
            crate->setPosition(glm::vec3(i*5, 2, (j * 5) + 5));
            crate->setScale(glm::vec3(1));
        }
    }

    addToScene(groundModel, std::vector<VertexFormat>(), "matShader", "ground");
    groundModel->setPosition(glm::vec3(0,0,0));

    
    camera->setLookAt(glm::vec3(0,0.5,-3));

    Game::Characters::Terry* terry = new Game::Characters::Terry(
        NULL,
        ShaderManager::GetShader("matShader"),
        projection,
        camera->getModelView(),
        camera
    );

    Game::Crosshairs::SimpleCross* crosshair = new Game::Crosshairs::SimpleCross(windowInfo.width, windowInfo.height);
    crosshair->SetProgram(ShaderManager::GetShader("chShader"));
    crosshair->Create();
    crosshair->SetCamera(this->camera);
    models_manager->AddModel("crosshair", crosshair);

    /* Setting up input */
    actorManager->AddActor("player", terry);
    inBuffer = false;
    mouseBuffer = 100;

    elapsedTime = 0;
    currentTime = 0;
    previousTime = 0;

    debugDrawer = new GLDebugDrawer();
    debugDrawer->setDebugMode(1);

    dynamicsWorld->setDebugDrawer(debugDrawer);
    dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawAabb | btIDebugDraw::DBG_DrawWireframe);
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
    newObject->setTextureManager(this->textureManager);
    newObject->SetLight(light);

    newObject->SetProgram(ShaderManager::GetShader(shaderName));
    newObject->SetProjection(projection);
    newObject->SetModelView(camera->getModelView());
    newObject->SetCamera(this->camera);
    newObject->Create(hitBox);
    newObject->setID(modelName);

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

    actorManager->GetActor("player").HandleInput(elapsedTime);

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
    this->castRays();
    debugDrawer->SetMatrices(this->camera->getModelView(), this->projection);
    dynamicsWorld->debugDrawWorld();
}

void FPSScene::notifyKeyboardUp(SDL_Keysym key) {
    keys[key.sym] = false;
}

void FPSScene::notifyKeyboardInput(unsigned char key, bool pressed) {
    if (key != SDLK_UNKNOWN) {
        Commands::Command* command = this->inputHandler->handleInput(key);
        if (command) {
            command->execute(actorManager->GetActor("player"), pressed);
        }
    }
}

int tmpButton;
int tmpState;
void FPSScene::notifyMouseInput(int button, int state, int x, int y) {
    if (button >= 0) {
        Commands::Command* command = this->inputHandler->handleInput(button);
        if (command) {
            command->execute(actorManager->GetActor("player"), state);
        }
    }
    tmpButton = button;
    tmpState = state;
}

// TODO: handle mouse input better for picking
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

    dynamicsWorld->setDebugDrawer(this->debugDrawer);
}

/**
 * This needs to be pulled apart carefully. I need to figure out which parts will be game logic, and what
 * will be physics manager stuff and what will be scene setup.
 * 
 * I need to keep as little game logic in here as possible. It should be all configuration.
*/
void FPSScene::castRays() {
    glm::vec3 end;
    glm::vec3 origin;

    this->camera->getPickRays(5.0f, &origin, &end);

    btVector3 btToRay = btVector3(end.x, end.y, end.z);
    btVector3 btFromRay = btVector3(origin.x, origin.y, origin.z);

    dynamicsWorld->updateAabbs();
    dynamicsWorld->computeOverlappingPairs();

    btCollisionWorld::ClosestRayResultCallback closestResult(btFromRay, btToRay);
    dynamicsWorld->rayTest(btFromRay, btToRay, closestResult);
    
    // if the left button is pressed
    if (closestResult.hasHit()) {
        const btRigidBody* pickedBody = btRigidBody::upcast(closestResult.m_collisionObject);
        if (tmpButton == 1 && tmpState == 1) {
            //check if the body isn't static or kinematic so that I know it can be moved
            if (pickedBody->getMass() != 0) {
                // Get the pointer to the ID of the object so I can pull it from the 
                std::string* shapeID = (std::string*)pickedBody->getUserPointer();
                Physics::PhysicsObject* pickedObject = physicsObjects[*shapeID];

                // Activate the object so physics stuff happens
                pickedObject->getRigidBody()->activate();
                // Set the object to the end location of the pick
                pickedObject->setPosition(end);
                // Turn gravity off so that it won't build up velocity while being held
                pickedObject->getRigidBody()->setGravity(btVector3(0.0f, 0.0f, 0.0f));
            }
        } else if (tmpButton == 1 && tmpState == 0) {  // if the left button is released
            std::string* shapeID = (std::string*)pickedBody->getUserPointer();
            Physics::PhysicsObject* pickedObject = physicsObjects[*shapeID];

            // Activate so physics things can happen
            pickedObject->getRigidBody()->activate();
            // TODO: Move this logic to the physics object so that I can use other logic to turn gravity on
            // Turn gravity back on
            pickedObject->getRigidBody()->setGravity(btVector3(0.0f, -15.0f, 0.0f));
        }
    }
}