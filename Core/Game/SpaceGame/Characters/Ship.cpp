#include "Ship.hpp"
#include "../../../../Manager/ShaderManager.hpp"

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
}

void Ship::TurnLeft()
{
}

void Ship::TurnUp()
{
}

void Ship::TurnDown()
{
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
