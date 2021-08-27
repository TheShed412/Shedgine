#include "FPSScene.hpp"
using namespace Graphics::Managers;
using namespace Game::Managers;

#include "../Rendering/Camera.hpp"
#include "../Rendering/Models/LoadedObject.hpp"
#include "../Core/Game/SpaceGame/Characters/Ship.hpp"
#include "../Core/Game/FPS/Characters/Terry.hpp"
#include "../Core/Game/FPS/Crosshairs/OpenGL/SimpleCross.hpp"
#include "../Core/Game/Commands/Command.hpp"
#include "../Core/Init/InitSDL.hpp"

// void collisionCheck(btDynamicsWorld *dynamicsWorld, btScalar timeStep) {
//     int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
// }

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
    eventManager = new Shed::EventManager();

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
    Models::LoadedObject* groundModel = new Models::LoadedObject("src/Models/big_floor.obj");
    

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 1; j++) {
            Models::LoadedObject* crate = new Models::LoadedObject("src/Models/new_crate.obj");
            addToScene(crate, "n64Shader", "crate" + std::to_string(i) + std::to_string(j));
            crate->setPosition(glm::vec3(i*5, 2, (j * 5) + 5));
            crate->setScale(glm::vec3(1));
        }
    }

    addToScene(groundModel,"matShader", "ground");
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
}

FPSScene::FPSScene(Core::WindowInfo windowInfo) : FPSScene() {
    this->windowInfo = windowInfo;
}

 
FPSScene::~FPSScene()
{   

    delete shader_manager;
    delete models_manager;
    delete camera;
}
 
void FPSScene::addToScene(Rendering::Models::LoadedObject* newObject, std::string shaderName, std::string modelName) {
    newObject->setTextureManager(this->textureManager);
    newObject->SetLight(light);

    newObject->SetProgram(ShaderManager::GetShader(shaderName));
    newObject->SetProjection(projection);
    newObject->SetModelView(camera->getModelView());
    newObject->SetCamera(this->camera);
    newObject->Create();

    models_manager->AddModel(modelName, newObject);
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
    // this->physicsManger->endFrameProcess(this->camera, this->elapsedTime);
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
        // this->physicsManger->setMouseState(button, state);
    }
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