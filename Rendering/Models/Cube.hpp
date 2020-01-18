#pragma once
#include "Model.hpp"

namespace Rendering
{
  namespace Models
  {
    class Cube : public Model
    {
      public:
        Cube();
       ~Cube();
 
        void Create();
        virtual void Update() override final;
        virtual void Draw() override final;

      private:
        GLuint ctm_location;
        GLuint projection_location;
        GLuint model_view_location;
        glm::mat4 ctm;
        glm::mat4 projection;
        glm::mat4 model_view;
        int vectors;
        std::vector<VertexFormat> makeCube(GLfloat size);
    };
  }
}