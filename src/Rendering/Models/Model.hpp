#pragma once
#include <vector>
#include <map>
#include "../IGameObject.hpp"
#include "../Camera.hpp"
#include "../Light.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
namespace Rendering
{
  namespace Models //create another namespace
  {
   class Model :public IGameObject
    {
      private:
        void setCtm();
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
         virtual void SetTranslation(glm::vec3);
         virtual void SetRotation(glm::quat);
         virtual const GLuint GetTexture(std::string textureName) const override;
				 virtual void SetTexture(std::string textureName, GLuint texture) override;
         virtual void processKeyboard(Movement direction, float deltaTime) override;
         virtual glm::vec2 GetRelativeScreenPosition();
         virtual GLuint GetVao() const override;
         virtual const std::vector<GLuint>& GetVbos() const override;
         void movementMat(glm::mat4);
         void SetScale(glm::vec3);
 
      protected:
        // TODO: camera and light may become lists since we can have more than one effecting an object
        // TODO: I need to add a function that lets me get either the projection and model view, or I need provide a function that returns the screen coords
        Camera* camera;
        Light* light;
        GLuint ctm_location;
        GLuint projection_location;
        GLuint model_view_location;
        glm::vec3 currentLocation;
        glm::vec3 translation;
        glm::mat4 rotation;
        glm::vec3 scale;
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