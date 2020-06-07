#pragma once
#include "Model.hpp"

namespace Rendering
{
  namespace Models
  {
    class Redical : public Model
    {
      public:
        Redical();
       ~Redical();
 
        void Create();
        virtual void Update() override final;
        virtual void Draw() override final;
        virtual void processKeyboard(Movement direction, float deltaTime) override final;

      private:
        int vectors;
        std::vector<VertexFormat> makeGrid();

    };
  }
}