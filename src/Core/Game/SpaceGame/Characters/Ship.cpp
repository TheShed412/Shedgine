#include "Ship.hpp"
#include "../../../../Manager/ShaderManager.hpp"
#include "../../../../Rendering/Light.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include <glm/gtx/matrix_decompose.hpp>

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
    currentYaw = 0;

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
    glm::mat4 newCtm = glm::rotate(glm::mat4(), 0.1f, glm::vec3(0, 0, -1.0));
    // model->SetCtm(&newCtm);
    return newCtm;
}

glm::mat4 Ship::TurnLeft()
{
    glm::mat4 newCtm = glm::rotate(glm::mat4(), 0.1f, glm::vec3(0, 0, 1.0));
    // model->SetCtm(&newCtm);
    return newCtm;
}

glm::mat4 Ship::TurnUp()
{
    glm::mat4 newCtm;
    // if(currentPitch <= 5.0) {
    //     currentPitch += 0.5f;
    //     newCtm = glm::rotate(glm::mat4();, 0.05f, glm::vec3(1.0, 0, 0));
    // } else {
    //     newCtm = glm::rotate(glm::mat4();, 0.0f, glm::vec3(1.0, 0, 0));
    // }
    newCtm = glm::translate(*this->model->GetCtm(), glm::vec3(0.0, 0.2, 0.0));
    // model->SetCtm(&newCtm);
    return newCtm;
}

glm::mat4 Ship::TurnDown()
{
    glm::mat4 newCtm;
    
    // if(currentPitch >= -5.0) {
    //     currentPitch -= 0.5f;
    //     newCtm = glm::rotate(glm::mat4(), 0.05f, glm::vec3(-1.0, 0, 0));
    // } else {
    //     newCtm = glm::rotate(glm::mat4(), 0.0f, glm::vec3(-1.0, 0, 0));
    // }
    newCtm = glm::translate(*this->model->GetCtm(), glm::vec3(0.0, -0.2, 0.0));
    // model->SetCtm(&newCtm);
    return newCtm;
}

void Ship::Action()
{
}

float generateTiltMatrices(glm::mat4* rotationMat, glm::mat4* translationMat, float currentTilt, float maxTilt, float tiltChange) {

    if(currentTilt <= maxTilt) {
        currentTilt += tiltChange;
        rotationMat = new glm::mat4(glm::rotate(*rotationMat, 0.05f, glm::vec3(0.0, 0, 1.0)));
    } else {
        rotationMat = new glm::mat4(glm::rotate(*rotationMat, 0.0f, glm::vec3(0.0, 0, 1.0)));
    }
    translationMat = new glm::mat4(glm::translate(*translationMat, glm::vec3(-0.2, 0.0, 0.0)));

    return currentTilt;
}


// TODO: pull some of this logic out
void Ship::HandleInput(unsigned char keys[] ) {
    if(keys['w'] || keys['a'] || keys['s'] || keys['d']) {
        glm::vec2 relScreenPos = model->GetRelativeScreenPosition();
        glm::mat4 rotationMats = glm::mat4(1.0);
        glm::mat4 translationMats = glm::mat4(1.0);
        if(keys['w']) {
            //camera->processKeyboard(Camera::FORWARD, 1);
            //translationMats = translationMats * this->TurnUp();
            if(currentPitch <= 3.0) {
                currentPitch += 0.5f;
                rotationMats = glm::rotate(rotationMats, 0.05f, glm::vec3(1.0, 0, 0));
            } else {
                rotationMats = glm::rotate(rotationMats, 0.0f, glm::vec3(1.0, 0, 0));
            }
            if (relScreenPos[1] < 0.99) {
                translationMats = glm::translate(translationMats, glm::vec3(0.0, 0.2, 0.0));
            }
        }
        if(keys['s']) {
            //camera->processKeyboard(Camera::BACKWARD, 1);
            //translationMats = translationMats * this->TurnDown();
            if(currentPitch >= -3.0) {
                currentPitch -= 0.5f;
                rotationMats = glm::rotate(rotationMats, 0.05f, glm::vec3(-1.0, 0, 0));
            } else {
                rotationMats = glm::rotate(rotationMats, 0.0f, glm::vec3(-1.0, 0, 0));
            }
            if (relScreenPos[1] > -0.99) {
                translationMats = glm::translate(translationMats, glm::vec3(0.0, -0.2, 0.0));
            }
        }
        if(keys['a']) {
            //camera->processKeyboard(Camera::LEFT, 1);
            //rotationMats = rotationMats + this->TurnLeft();
            //rotationMats = glm::rotate(rotationMats, 0.1f, glm::vec3(0, 0, 1.0));

            if(currentYaw >= -3.0) {
                currentYaw -= 0.5f;
                rotationMats = glm::rotate(rotationMats, 0.05f, glm::vec3(0.0, 0, 1.0));
            } else {
                rotationMats = glm::rotate(rotationMats, 0.0f, glm::vec3(0.0, 0, 1.0));
            }
            if (relScreenPos[0] > -0.99) {
                translationMats = glm::translate(translationMats, glm::vec3(-0.2, 0.0, 0.0));
            }
        }
        if(keys['d']) {
            //camera->processKeyboard(Camera::RIGHT, 1);
            //rotationMats = rotationMats + this->TurnRight();
            //rotationMats = glm::rotate(rotationMats, 0.1f, glm::vec3(0, 0, -1.0));
            
            if(currentYaw <= 3.0) {
                currentYaw += 0.5f;
                rotationMats = glm::rotate(rotationMats, 0.05f, glm::vec3(0.0, 0, -1.0));
            } else {
                rotationMats = glm::rotate(rotationMats, 0.0f, glm::vec3(0.0, 0, -1.0));
            }
            if (relScreenPos[0] < 0.99) {
                translationMats = glm::translate(translationMats, glm::vec3(0.2, 0.0, 0.0));
            }
        }

        glm::mat4 newCtm;
        newCtm = translationMats * *this->model->GetCtm() * rotationMats;
        this->model->SetCtm(&newCtm);
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

glm::vec3 Ship::GetCoords() 
{
    return glm::vec3((*this->model->GetCtm())[3]);
}
