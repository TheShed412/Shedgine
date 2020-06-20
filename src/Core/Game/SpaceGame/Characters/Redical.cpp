// #include "Redical.hpp"
// #include "../../../../Manager/ShaderManager.hpp"
// #include "../../../../Rendering/Light.hpp"

// using namespace Game;
// using namespace Characters;

// Redical::Redical() {}
// Redical::~Redical()
// {
//     model->Destroy();
// }

// Redical::Redical(Rendering::Models::LoadedObject* model,
// GLuint program,
// glm::mat4 projection,
// glm::mat4 modelView,
// Rendering::Camera* camera) 
// {
//     model->SetProgram(program);
//     model->SetProjection(projection);
//     model->SetModelView(camera->getModelView());
//     model->SetCamera(camera);
//     model->Create();

//     this->model = model;
// }

// Redical::Redical(Rendering::Models::Redical* model,
// GLuint program,
// glm::mat4 projection,
// glm::mat4 modelView,
// Rendering::Camera* camera) 
// {
//     model->SetProgram(program);
//     model->SetProjection(projection);
//     model->SetModelView(camera->getModelView());
//     model->SetCamera(camera);
//     model->Create();

//     this->redicalModel = model;
// }

// void Redical::Update()
// {
//     redicalModel->Update();
// }

// void Redical::Draw()
// {
//     redicalModel->Draw();
// }

// void Redical::Create()
// {
//     redicalModel->Create();
// }

// void Redical::Destroy() {
//     redicalModel->Destroy();
// }

// glm::mat4 Redical::MoveForward()
// {
//     return glm::mat4(0);
// }

// glm::mat4 Redical::MoveBackward()
// {
//     return glm::mat4(0);
// }

// glm::mat4 Redical::MoveRight()
// {
//     return glm::mat4(0);
// }

// glm::mat4 Redical::MoveLeft()
// {
//     return glm::mat4(0);
// }

// glm::mat4 Redical::MoveUp()
// {
//     return glm::mat4(0);
// }

// glm::mat4 Redical::MoveDown()
// {
//     return glm::mat4(0);
// }

// glm::mat4 Redical::TurnRight()
// {
//     glm::mat4 newCtm = glm::rotate(*model->GetCtm(), 0.05f, glm::vec3(0, 0, -1.0));
//     model->SetCtm(&newCtm);
//     return glm::mat4(0);
// }

// glm::mat4 Redical::TurnLeft()
// {
//     glm::mat4 newCtm = glm::rotate(*model->GetCtm(), 0.05f, glm::vec3(0, 0, 1.0));
//     model->SetCtm(&newCtm);
//     return glm::mat4(0);
// }

// glm::mat4 Redical::TurnUp()
// {
//     glm::mat4 newCtm;
//     // if(currentPitch <= 5.0) {
//     //     currentPitch += 0.5f;
//     //     newCtm = glm::rotate(*model->GetCtm(), 0.05f, glm::vec3(1.0, 0, 0));
//     // } else {
//     //     newCtm = glm::rotate(*model->GetCtm(), 0.0f, glm::vec3(1.0, 0, 0));
//     // }
//     newCtm = glm::translate(*model->GetCtm(), glm::vec3(0.0, 0.1, 0.0));
//     model->SetCtm(&newCtm);
//     return glm::mat4(0);
// }

// glm::mat4 Redical::TurnDown()
// {
//     glm::mat4 newCtm;
    
//     // if(currentPitch >= -5.0) {
//     //     currentPitch -= 0.5f;
//     //     newCtm = glm::rotate(*model->GetCtm(), 0.05f, glm::vec3(-1.0, 0, 0));
//     // } else {
//     //     newCtm = glm::rotate(*model->GetCtm(), 0.0f, glm::vec3(-1.0, 0, 0));
//     // }
//     newCtm = glm::translate(*model->GetCtm(), glm::vec3(0.0, -0.1, 0.0));
//     model->SetCtm(&newCtm);
//     return glm::mat4(0);
// }

// void Redical::Action()
// {
// }

// void Redical::HandleInput(unsigned char keys[] ) {

// }
