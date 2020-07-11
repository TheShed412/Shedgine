#include "FPSScene.hpp"
using namespace Managers;

#include "../Rendering/Camera.hpp"
#include "../Core/Game/SpaceGame/Characters/Ship.hpp"
#include "../Core/Game/FPS/Characters/Terry.hpp"
 
FPSScene::FPSScene()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);  
    glEnable(GL_DEPTH_TEST);
    gameObjectManager = new Game::Managers::ObjectManager();
    actorManager = new Game::Managers::ActorManager();
    shader_manager = new ShaderManager();
    // TODO: make it so I can control the speed with the player
    camera = new Camera(glm::vec3(0,0.5,10), glm::vec3(0,1,0), 0.2, 0.1);
    light = new Light(
        glm::vec3(0,10,0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, 1.0, 1.0),
        0.1,
        0.001,
        0.001
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

    Models::LoadedObject* groundModel = new Models::LoadedObject("src/Models/path.obj");
    Models::LoadedObject* shipModel = new Models::LoadedObject("src/Models/ship2.obj");
    shipModel->SetLight(light);
    groundModel->SetLight(light);

    groundModel->SetProgram(ShaderManager::GetShader("matShader"));
    groundModel->SetProjection(projection);
    groundModel->SetModelView(camera->getModelView());
    groundModel->SetCamera(this->camera);
    groundModel->Create();

    shipModel->SetProgram(ShaderManager::GetShader("matShader"));
    shipModel->SetProjection(projection);
    shipModel->SetModelView(camera->getModelView());
    shipModel->SetCamera(this->camera);
    shipModel->Create();

    //unsigned int texture = textureLoader->LoadTexture("Textures/Crate.bmp", 256, 256);

    //models_manager->AddModel("ship", shipModel);
    camera->setLookAt(glm::vec3(0,-1,-3));

    Game::Characters::Terry* terry = new Game::Characters::Terry(
        NULL,
        ShaderManager::GetShader("matShader"),
        projection,
        camera->getModelView(),
        camera
    );

    /* Setting up input */
    actorManager->AddActor("player", terry);
    models_manager->AddModel("ground", groundModel);
    inBuffer = false;
    mouseBuffer = 100;

    setupCollisions();

    dynamicsWorld->setGravity(btVector3(0,-10,0));
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
 
void FPSScene::notifyBeginFrame()
{
    actorManager->GetActor("player").HandleInput(keys);
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


void FPSScene::notifyMouseMovementInput(int x, int y) {
    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    // If I am in the buffer, I don't want to update since I may be in the middle of warping the cursor
    // back to the center of the screen
    if (!inBuffer) {
        float xoffset = x - lastX;
        float yoffset = lastY - y; // reversed since y-coordinates go from bottom to top

        lastX = x;
        lastY = y;
        actorManager->GetActor("player").HandleMouseInput(xoffset, yoffset);
    }
    
    glutPostRedisplay();

    int win_h = windowInfo.height;
    int win_w = windowInfo.width;

    if ( x < mouseBuffer || x > win_w - mouseBuffer ) {
        inBuffer = true;
        lastX = win_w/2;
        lastY = win_h/2;
        glutWarpPointer(win_w/2, win_h/2);  //centers the cursor
    } else if (y < mouseBuffer || y > win_h - mouseBuffer) {
        inBuffer = true;
        lastX = win_w/2;
        lastY = win_h/2;
        glutWarpPointer(win_w/2, win_h/2);
    }
    else {
        inBuffer = false;
    }
    
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