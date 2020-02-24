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
        LoadedObject(std::string filename);
       ~LoadedObject();
 
        void Create();
        virtual void Update() override final;
        virtual void Draw() override final;

      private:
        int vectors;
        std::string filename;
        std::vector<VertexFormat> makeObject();
    };
  }
}