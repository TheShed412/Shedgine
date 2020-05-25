#pragma once
#include "Model.hpp"

namespace Rendering
{
  namespace Models
  {
    class Grid : public Model
    {
      public:
        Grid();
       ~Grid();
 
        void Create();
        virtual void Update() override final;
        virtual void Draw(Light) override final;
        virtual void processKeyboard(Movement direction, float deltaTime) override final;

      private:
        int vectors;
        std::vector<VertexFormat> makeGrid();

    };
  }
}