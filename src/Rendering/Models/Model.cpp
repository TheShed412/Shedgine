#include "Model.hpp"
using namespace Rendering;
using namespace Models;
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include <glm/gtx/quaternion.hpp>
 
Model::Model(){
  this->rotation = glm::mat4(1.0f);
  this->scale = glm::vec3(1,1,1);
  this->translation = glm::vec3(0);
}
 
Model::~Model()
{
   Destroy();
}
 
void Model::Draw()
{
   //this will be again overridden
}
 
void Model::Update()
{
 //this will be again overridden
}

void Model::processKeyboard(Movement direction, float deltaTime) {
    
}
 
void Model::SetProgram(GLuint program)
{
  this->program = program;
}

void Model::SetModelView(glm::mat4 modelView)
{
  this->model_view = modelView;
}

void Model::SetCamera(Camera* camera)
{
  this->camera = camera;
}

void Model::SetLight(Light* light)
{
  this->light = light;
}

void Model::SetProjection(glm::mat4 projection)
{
  this->projection = projection;
}
 
GLuint Model::GetVao() const
{
  return vao;
}
 
const std::vector<GLuint>& Model::GetVbos() const
{
   return vbos;
}

bool rotApplied = false;
void Model::SetTranslation(glm::vec3 pos) {
  this->translation = pos;
  this->setCtm();
}

void Model::setCtm() {
  std::cout << "SCALE: " << glm::to_string(this->scale) << std::endl;
  glm::mat4 transMat = glm::scale(glm::translate(glm::mat4(1.0), translation) * rotation, this->scale);
  this->ctm = transMat * this->ctm;

  // Reset so that it is only applied once updated
  this->rotation = glm::mat4(1.0);
  this->translation = glm::vec3(0);
}

void Model::movementMat(glm::mat4 newMovementMat) {
  this->ctm = newMovementMat;
  
  this->ctm = glm::scale(this->ctm, scale);
}

// Will make a local rotation
void Model::SetRotation(glm::quat rotation) {
  float x = this->ctm[3].x;
  float y = this->ctm[3].y;
  float z = this->ctm[3].z;
  glm::vec3 backToOgVec = glm::vec3(-x, -y, -z);
  glm::vec3 toPos = glm::vec3(x, y, z);
  glm::mat4 backToOgMat = glm::translate(glm::mat4(1.0), backToOgVec);
  glm::mat4 backToPosMat = glm::translate(glm::mat4(1.0), toPos);
  
  this->rotation = backToPosMat * glm::toMat4(rotation) * backToOgMat;

  this->setCtm();
  rotApplied = true;
}

void Model::SetScale(glm::vec3 scale) {
  this->scale = scale;

  this->setCtm();
}
 
void Model::Destroy()
{
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(vbos.size(), &vbos[0]);
  vbos.clear();
  if (textures.size() > 0)
	{
		for (auto t: textures)
		{
			glDeleteTextures(1, &t.second);
		}
		textures.clear();
	}
}

void Model::SetTexture(std::string textureName, GLuint texture) {
  if (texture == 0) return;
	textures[textureName] = texture;
}

const GLuint Model::GetTexture(std::string textureName) const {
  GLuint tex = textures.at(textureName);
  return tex;
}

glm::vec2 Model::GetRelativeScreenPosition() {
  glm::vec3 position = ctm[3];
  glm::vec4 clipSpace = projection * (model_view * glm::vec4(position, 1.0));

  if (clipSpace[3] == 0) {
    float minFloat = -std::numeric_limits<float>::max();
    return glm::vec2(minFloat, minFloat);//maybe return something else?
  }
  float nX = clipSpace[0] / clipSpace[3];
  float nY = clipSpace[1] / clipSpace[3];
  
  glm::vec2 ndcXY = glm::vec2(nX, nY);

  //glm::vec2 windowSpace = ((ndcXY + 1.0f) / 2.0f) * glm::vec2(screenWidth, screenHeight) + glm::vec2(screenPosX, screenPosY);

  return ndcXY;
}