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
        std::vector<VertexFormat> makeCube(GLfloat size);
    };
  }
}