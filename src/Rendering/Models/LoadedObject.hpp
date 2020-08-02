#pragma once
#include "Model.hpp"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

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
        virtual const glm::mat4* GetCtm();
        virtual void SetCtm(glm::mat4*);
        std::vector<VertexFormat> getVerts();
        void setPosition(glm::vec3);
        void setRotation(glm::vec3);

      private:
        glm::vec3 lastAngles;
        std::vector<TextureFormat> textures;
        std::vector<Mesh> meshes;
        int vectors;
        std::string filename;
        std::string directory;
        std::vector<VertexFormat> makeObject();
        std::vector<VertexFormat> loadObject();
        std::vector<VertexFormat> vertices;
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        void processNode(aiNode *node, const aiScene *scene);
        std::vector<TextureFormat> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory);
        void processKeyboard(Movement direction, float deltaTime);
    };
  }
}