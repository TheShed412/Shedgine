#pragma once
#include "Model.hpp"

namespace Rendering
{
  namespace Models
  {
    class LoadedObject : public Model
    {
      public:
        LoadedObject();
       ~LoadedObject();
 
        void Create();
        virtual void Update() override final;
        virtual void Draw() override final;

      private:
        int vectors;
        std::vector<VertexFormat> makeObject();
    };
  }
}