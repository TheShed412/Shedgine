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

glm::mat4 Terry::MoveForward()
{
    return glm::mat4(0);
}

glm::mat4 Terry::MoveBackward()
{
}

glm::mat4 Terry::MoveRight()
{
}

glm::mat4 Terry::MoveLeft()
{
}

glm::mat4 Terry::MoveUp()
{
}

glm::mat4 Terry::MoveDown()
{
}

glm::mat4 Terry::TurnRight()
{

}

glm::mat4 Terry::TurnLeft()
{

}

glm::mat4 Terry::TurnUp()
{

}

glm::mat4 Terry::TurnDown()
{

}

void Terry::Action()
{
}

void Terry::HandleInput(bool keys[], int deltaTime) {
    if(keys['w'] || keys['a'] || keys['s'] || keys['d']) {
        if (keys['w'])
        {
            camera->processKeyboard(Rendering::Camera::FORWARD, deltaTime/1000.0f);
        }
        if (keys['a'])
        {
            camera->processKeyboard(Rendering::Camera::LEFT, deltaTime/1000.0f);
        }
        if (keys['s'])
        {
            camera->processKeyboard(Rendering::Camera::BACKWARD, deltaTime/1000.0f);
        }
        if (keys['d'])
        {
            camera->processKeyboard(Rendering::Camera::RIGHT, deltaTime/1000.0f);
        }
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
