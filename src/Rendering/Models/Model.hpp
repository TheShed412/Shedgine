#pragma once
#include <vector>
#include <map>
#include "../IGameObject.hpp"
#include "../Camera.hpp"
#include "../Light.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace Rendering
{
  namespace Models //create another namespace
  {
   class Model :public IGameObject
    {
     public:
         Model();
         virtual ~Model();
         // methods from interface
         virtual void Draw() override;
         virtual void Update() override;
         virtual void SetProgram(GLuint shaderName) override;
         virtual void SetModelView(glm::mat4 modelView);
         virtual void SetProjection(glm::mat4 projection);
         virtual void SetCamera(Camera* camera);
         virtual void SetLight(Light* light);
         virtual void Destroy() override;
         virtual const GLuint GetTexture(std::string textureName) const override;
				 virtual void SetTexture(std::string textureName, GLuint texture) override;
         virtual void processKeyboard(Movement direction, float deltaTime) override;
 
         virtual GLuint GetVao() const override;
         virtual const std::vector<GLuint>& GetVbos() const override;
 
      protected:
        // TODO: camera and light may become lists since we can have more than one effecting an object
        Camera* camera;
        Light* light;
        GLuint ctm_location;
        GLuint projection_location;
        GLuint model_view_location;
        glm::vec3 currentLocation;
        glm::mat4 ctm;
        glm::mat4 projection;
        glm::mat4 model_view;
        GLuint vao;
        GLuint program;
        std::vector<GLuint> vbos;
        std::map<std::string, GLuint> textures;
   };
  }
}