#include "Ship.hpp"
#include "../../../../Manager/ShaderManager.hpp"
#include "../../../../Rendering/Light.hpp"

using namespace Game;
using namespace Characters;

Ship::Ship() {}
Ship::~Ship()
{
    model->Destroy();
}

Ship::Ship(Rendering::Models::LoadedObject* shipModel,
GLuint program,
glm::mat4 projection,
glm::mat4 modelView,
Rendering::Camera* camera) 
{
    shipModel->SetProgram(program);
    shipModel->SetProjection(projection);
    shipModel->SetModelView(camera->getModelView());
    shipModel->SetCamera(camera);
    shipModel->Create();

    currentPitch = 0;

    this->model = shipModel;
}

void Ship::Update()
{
    model->Update();
}

void Ship::Draw()
{
    model->Draw();
}

void Ship::Create()
{
    model->Create();
}

void Ship::Destroy() {
    model->Destroy();
}

glm::mat4 Ship::MoveForward()
{
    return glm::mat4(0);
}

glm::mat4 Ship::MoveBackward()
{
}

glm::mat4 Ship::MoveRight()
{
}

glm::mat4 Ship::MoveLeft()
{
}

glm::mat4 Ship::MoveUp()
{
}

glm::mat4 Ship::MoveDown()
{
}

glm::mat4 Ship::TurnRight()
{
    glm::mat4 newCtm = glm::rotate(*model->GetCtm(), 0.1f, glm::vec3(0, 0, -1.0));
    model->SetCtm(&newCtm);
    return newCtm;
}

glm::mat4 Ship::TurnLeft()
{
    glm::mat4 newCtm = glm::rotate(*model->GetCtm(), 0.1f, glm::vec3(0, 0, 1.0));
    model->SetCtm(&newCtm);
    return newCtm;
}

glm::mat4 Ship::TurnUp()
{
    glm::mat4 newCtm;
    // if(currentPitch <= 5.0) {
    //     currentPitch += 0.5f;
    //     newCtm = glm::rotate(*model->GetCtm(), 0.05f, glm::vec3(1.0, 0, 0));
    // } else {
    //     newCtm = glm::rotate(*model->GetCtm(), 0.0f, glm::vec3(1.0, 0, 0));
    // }
    newCtm = glm::translate(*model->GetCtm(), glm::vec3(0.0, 0.2, 0.0));
    model->SetCtm(&newCtm);
    return newCtm;
}

glm::mat4 Ship::TurnDown()
{
    glm::mat4 newCtm;
    
    // if(currentPitch >= -5.0) {
    //     currentPitch -= 0.5f;
    //     newCtm = glm::rotate(*model->GetCtm(), 0.05f, glm::vec3(-1.0, 0, 0));
    // } else {
    //     newCtm = glm::rotate(*model->GetCtm(), 0.0f, glm::vec3(-1.0, 0, 0));
    // }
    newCtm = glm::translate(*model->GetCtm(), glm::vec3(0.0, -0.2, 0.0));
    model->SetCtm(&newCtm);
    return newCtm;
}

void Ship::Action()
{
}

void Ship::HandleInput(unsigned char keys[] ) {
    if(keys['w']) {
        //camera->processKeyboard(Camera::FORWARD, 1);
        this->TurnUp();
    }
    if(keys['s']) {
        //camera->processKeyboard(Camera::BACKWARD, 1);
        this->TurnDown();
    }
    if(keys['a']) {
        //camera->processKeyboard(Camera::LEFT, 1);
        this->TurnLeft();
    }
    if(keys['d']) {
        //camera->processKeyboard(Camera::RIGHT, 1);
        this->TurnRight();
    }
}

void Ship::SetFlightSpeed(float flightSpeed)
{
    this->flightSpeed = flightSpeed;
}

void Ship::SetPitch(float max, float delta)
{
    this->maxPitch = max;
    this->pitchDelta = delta;
}

void Ship::SetYaw(float max, float delta)
{
    this->maxYaw = max;
    this->yawDelta = delta;
}

void Ship::SetRoll(float max, float delta)
{
    this->maxRoll = max;
    this->rollDelta = delta;
}
