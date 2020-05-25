#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "../VertexFormat.hpp"
#include "../TextureFormat.hpp"

namespace Rendering
{
  namespace Models
  {

    struct Material {
      //Material color lighting
      glm::vec4 Ka;
      //Diffuse reflection
      glm::vec4 Kd;
      //Mirror reflection
      glm::vec4 Ks;
    };


    class Mesh
    {
        // TODO: make a destroy method
        public:
            Mesh(std::vector<VertexFormat> vertices, std::vector<unsigned int> indices, std::vector<TextureFormat> textures, Material mat);
            Mesh();
            std::vector<VertexFormat> getVertices();
            std::vector<unsigned int> getIndecies();
            std::vector<TextureFormat> getTextures();
            void Draw(GLuint program, 
                GLuint ctm_location,
                GLuint projection_location,
                GLuint model_view_location,
                glm::mat4 ctm,
                glm::mat4 projection,
                glm::mat4 model_view);
            unsigned int getVAO();
            unsigned int getVBO();
            unsigned int getEBO();
            
        private:
            std::vector<VertexFormat> vertices;
            std::vector<unsigned int> indices;
            std::vector<TextureFormat> textures;
            Material mat;
            unsigned int VAO, VBO, EBO, uniformBlockIndex;
            void setupMesh();

    };
  }
}