#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <vector>
#include <GL/glew.h>

#include "../VertexFormat.hpp"
#include "../TextureFormat.hpp"
#include "../Light.hpp"

namespace Rendering
{
  namespace Models
  {

    // make these in to objects
    struct Material {
      //Material color lighting
      glm::vec4 Ka;
      //Diffuse reflection
      glm::vec4 Kd;
      //Mirror reflection
      glm::vec4 Ks;
      // shininess
      float Ns;
    };


    class Mesh
    {
        // TODO: make a destroy method
        public:
            Mesh(std::vector<VertexFormat> vertices, std::vector<unsigned int> indices, std::vector<TextureFormat> textures, Material mat, GLuint program);
            Mesh();
            std::vector<VertexFormat> getVertices();
            std::vector<unsigned int> getIndecies();
            std::vector<TextureFormat> getTextures();
            void Draw(glm::mat4 ctm,
                glm::mat4 projection,
                glm::mat4 model_view,
                Light* light);
            unsigned int getVAO();
            unsigned int getVBO();
            unsigned int getEBO();
            
        private:
            std::vector<VertexFormat> vertices;
            std::vector<unsigned int> indices;
            std::vector<TextureFormat> textures;
            Material mat;
            Light* light;
            GLuint program;
            GLuint ctm_location;
            GLuint projection_location;
            GLuint model_view_location;
            GLuint ambient_location;
            GLuint position_location;
            GLuint specular_location;
            GLuint diffuse_location;
            GLuint constant_location;
            GLuint linear_location;
            GLuint quadratic_location;
            unsigned int VAO, VBO, EBO, uniformBlockIndex, lightObject;
            void setupMesh();

    };
  }
}