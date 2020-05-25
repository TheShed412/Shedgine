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
    };

    // There is a light object as well, this is purely to pass to the shader
    struct sLight {
      glm::vec3 position;  
    
      glm::vec3 ambient;
      glm::vec3 diffuse;
      glm::vec3 specular;
    
      float constant;
      float linear;
      float quadratic;
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
            void Draw(GLuint program, 
                GLuint ctm_location,
                GLuint projection_location,
                GLuint model_view_location,
                glm::mat4 ctm,
                glm::mat4 projection,
                glm::mat4 model_view,
                Light light);
            unsigned int getVAO();
            unsigned int getVBO();
            unsigned int getEBO();
            
        private:
            std::vector<VertexFormat> vertices;
            std::vector<unsigned int> indices;
            std::vector<TextureFormat> textures;
            Material mat;
            sLight light;
            GLuint program;
            unsigned int VAO, VBO, EBO, uniformBlockIndex, lightObject;
            void setupMesh();

    };
  }
}