#include "Model.hpp"
using namespace Rendering;
using namespace Models;
 
Model::Model(){}
 
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