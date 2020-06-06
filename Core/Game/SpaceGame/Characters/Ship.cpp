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

void Ship::MoveForward()
{
}

void Ship::MoveBackward()
{
}

void Ship::MoveRight()
{
}

void Ship::MoveLeft()
{
}

void Ship::MoveUp()
{
}

void Ship::MoveDown()
{
}

void Ship::TurnRight()
{
    glm::mat4 newCtm = glm::rotate(*model->GetCtm(), 0.05f, glm::vec3(0, 0, -1.0));
    model->SetCtm(&newCtm);
}

void Ship::TurnLeft()
{
    glm::mat4 newCtm = glm::rotate(*model->GetCtm(), 0.05f, glm::vec3(0, 0, 1.0));
    model->SetCtm(&newCtm);
}

void Ship::TurnUp()
{
    glm::mat4 newCtm;
    // if(currentPitch <= 5.0) {
    //     currentPitch += 0.5f;
    //     newCtm = glm::rotate(*model->GetCtm(), 0.05f, glm::vec3(1.0, 0, 0));
    // } else {
    //     newCtm = glm::rotate(*model->GetCtm(), 0.0f, glm::vec3(1.0, 0, 0));
    // }
    newCtm = glm::translate(*model->GetCtm(), glm::vec3(0.0, 0.1, 0.0));
    model->SetCtm(&newCtm);

}

void Ship::TurnDown()
{
    glm::mat4 newCtm;
    
    // if(currentPitch >= -5.0) {
    //     currentPitch -= 0.5f;
    //     newCtm = glm::rotate(*model->GetCtm(), 0.05f, glm::vec3(-1.0, 0, 0));
    // } else {
    //     newCtm = glm::rotate(*model->GetCtm(), 0.0f, glm::vec3(-1.0, 0, 0));
    // }
    newCtm = glm::translate(*model->GetCtm(), glm::vec3(0.0, -0.1, 0.0));
    model->SetCtm(&newCtm);
}

void Ship::Action()
{
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
