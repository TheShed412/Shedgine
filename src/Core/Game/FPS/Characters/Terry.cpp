#include "Terry.hpp"
#include "../../../../Manager/ShaderManager.hpp"
#include "../../../../Rendering/Light.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include <glm/gtx/matrix_decompose.hpp>

using namespace Game;
using namespace Characters;

Terry::Terry() {}
Terry::~Terry()
{
    model->Destroy();
}

Terry::Terry(Rendering::Models::LoadedObject* model,
GLuint program,
glm::mat4 projection,
glm::mat4 modelView,
Rendering::Camera* camera) 
{
    // TODO: add a model
    // model->SetProgram(program);
    // model->SetProjection(projection);
    // model->SetModelView(camera->getModelView());
    // model->SetCamera(camera);
    // model->Create();

    this->model = model;
    this->camera = camera;
    this->moveForward = false;
    this->moveBack = false;
    this->moveLeft = false;
    this->moveRight = false;
}

void Terry::Update()
{
    model->Update();
}

void Terry::Draw()
{
    model->Draw();
}

void Terry::Create()
{
    model->Create();
}

void Terry::Destroy() {
    model->Destroy();
}

void Terry::MoveForward(bool move)
{
    moveForward = move;
}

void Terry::MoveBackward(bool move)
{
    moveBack = move;
}

void Terry::MoveRight(bool move)
{
    moveRight = move;
}

void Terry::MoveLeft(bool move)
{
    moveLeft = move;
}

void Terry::MoveUp(int deltaTime)
{
}

void Terry::MoveDown(int deltaTime)
{
}

void Terry::TurnRight(int deltaTime)
{

}

void Terry::TurnLeft(int deltaTime)
{

}

void Terry::TurnUp(int deltaTime)
{

}

void Terry::TurnDown(int deltaTime)
{

}

void Terry::Action(int deltaTime)
{
}

void Terry::HandleInput(int deltaTime) {
    if (moveForward) {
        camera->processKeyboard(Rendering::Camera::FORWARD, deltaTime/1000.0f);
    }

    if (moveLeft) {
        camera->processKeyboard(Rendering::Camera::LEFT, deltaTime/1000.0f);
    }

    if (moveBack) {
        camera->processKeyboard(Rendering::Camera::BACKWARD, deltaTime/1000.0f);
    }

    if (moveRight) {
        camera->processKeyboard(Rendering::Camera::RIGHT, deltaTime/1000.0f);
    }
}


void Terry::LookAtObject(glm::vec3 lookAtPoint) {

}

glm::vec3 Terry::GetCoords() 
{
    return glm::vec3((*this->model->GetCtm())[3]);
}

void Terry::HandleMouseInput(int x, int y) {
    camera->processMouseMovement(x, y);
}

void Terry::HandleLeftMouse(bool pressed) {
    this->leftPressed = pressed;
}

void Terry::HandleRightMouse(bool pressed) {
    this->rightpressed = pressed;
}
