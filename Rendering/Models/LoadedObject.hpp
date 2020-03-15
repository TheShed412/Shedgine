#pragma once
#include "Model.hpp"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <stb_image.h>

#include "../TextureFormat.hpp"
#include "Mesh.hpp"

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
        std::vector<TextureFormat> textures;
        std::vector<Mesh> meshes;
        int vectors;
        std::string filename;
        std::string directory;
        std::vector<VertexFormat> makeObject();
        std::vector<VertexFormat> loadObject();
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        void processNode(aiNode *node, const aiScene *scene);
    };
  }
}