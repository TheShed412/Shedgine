#pragma once
#include "Model.hpp"

namespace Rendering
{
  namespace Models
  {
    class Torus : public Model
    {
      public:
        Torus();
       ~Torus();
 
        void Create();
        virtual void Update() override final;
        virtual void Draw() override final;
    };
  }
}