#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <vector>

#include "../VertexFormat.hpp"
#include "../TextureFormat.hpp"

namespace Rendering
{
  namespace Models
  {
    class Mesh
    {
        // TODO: make a destroy method
        public:
            Mesh(std::vector<VertexFormat> vertices, std::vector<unsigned int> indices, std::vector<TextureFormat> textures);
            Mesh();
            std::vector<VertexFormat> getVertices();
            std::vector<unsigned int> getIndecies();
            std::vector<TextureFormat> getTextures();
            unsigned int getVAO();
            unsigned int getVBO();
            unsigned int getEBO();
            
        private:
            std::vector<VertexFormat> vertices;
            std::vector<unsigned int> indices;
            std::vector<TextureFormat> textures;
            unsigned int VAO, VBO, EBO;
            void setupMesh();

    };
  }
}