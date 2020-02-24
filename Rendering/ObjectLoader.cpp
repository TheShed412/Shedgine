#include "ObjectLoader.hpp"

using namespace Rendering;

ObjectLoader::ObjectLoader(/* args */)
{
}
    
ObjectLoader::~ObjectLoader()
{
}

bool ObjectLoader::hasUvIndexes(std::string face) {
    std::string dividerStr = "//"; 

    size_t found = face.find(dividerStr);
    if(found != std::string::npos) {
        return false;
    }

    return true;
}

std::vector<VertexFormat> ObjectLoader::LoadObject(const std::string& filename) {
    std::vector<VertexFormat> thing;

    std::vector<int> vector_indecies, uv_indices, noramal_indecies;
    std::vector<glm::vec3> temp_verts;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_norms;

    std::ifstream model(filename.c_str(), std::ios::in);
    if (!model.good()) {
        std::cout << "Won't open" << std::endl;
        return thing;
    }

    std::string modelLine;
    while(getline(model, modelLine)) {
        //check if the first character is a vertex
        std::istringstream modelLineStream(modelLine);

        std::string typeStr;
        modelLineStream >> typeStr;
        if(typeStr == "v") {
            glm::vec3 vertex;
            modelLineStream >> vertex.x >> vertex.y >> vertex.z;
            temp_verts.push_back(vertex);
        } else if(typeStr == "vn") {
            glm::vec3 normal;
            modelLineStream >> normal.x >> normal.y >> normal.z;
            temp_norms.push_back(normal);
        } else if(typeStr == "vt") {
            glm::vec2 uv;
            modelLineStream >> uv.x >> uv.y;
            temp_uvs.push_back(uv);
        } else if(typeStr == "f") {
            // Each one of these are going to be a vertex in a mesh
            // /int/int:
            std::string face1;
            std::string face2;
            std::string face3;
            modelLineStream >> face1 >> face2 >> face3;

            // I need to check for the case that the texture vertex doesn't exist. poo
            if (hasUvIndexes(face1)) {
                int vertIndex[3], uvIndex[3], normalIndex[3];
                sscanf(face1.c_str(), "%d/%d/%d", &vertIndex[0], &uvIndex[0], &normalIndex[0]);
                sscanf(face2.c_str(), "%d/%d/%d", &vertIndex[1], &uvIndex[1], &normalIndex[1]);
                sscanf(face3.c_str(), "%d/%d/%d", &vertIndex[2], &uvIndex[2], &normalIndex[2]);
                for(int i = 0; i < 3; i++) {
                    vector_indecies.push_back(vertIndex[i]);
                    noramal_indecies.push_back(normalIndex[i]);
                    uv_indices.push_back(uvIndex[i]);
                }
            } else {
                int vertIndex[3], normalIndex[3];
                sscanf(face1.c_str(), "%d//%d", &vertIndex[0], &normalIndex[0]);
                sscanf(face2.c_str(), "%d//%d", &vertIndex[1], &normalIndex[1]);
                sscanf(face3.c_str(), "%d//%d", &vertIndex[2], &normalIndex[2]);
                for(int i = 0; i < 3; i++) {
                    vector_indecies.push_back(vertIndex[i]);
                    noramal_indecies.push_back(normalIndex[i]);
                }
            }
        }
    }

    /*
        Processing step. Take the f part and use it to construct our outputs
    */

   
   for(int i = 0; i < vector_indecies.size(); i++) {
       int vector_index = vector_indecies[i];// this will fill the mesh indecies array
       glm::vec3 vector = temp_verts[vector_index-1];
       temp_verts.push_back(vector);
   }

   for(int i = 0; i < uv_indices.size(); i++) {
       int uv_index = uv_indices[i];// this will fill the mesh indecies array
       glm::vec2 uv = temp_uvs[uv_index-1];
       temp_uvs.push_back(uv);
   }

   for(int i = 0; i < noramal_indecies.size(); i++) {
       int norm_index = noramal_indecies[i];// this will fill the mesh indecies array
       glm::vec3 norm = temp_norms[norm_index-1];
       temp_norms.push_back(norm);
   }

   /**
    * Creating a Mesh from the stuff above
   */

    // std::vector<VertexFormat> vertices;
    // std::vector<unsigned int> indecies;
    // std::vector<VertexTexture> textures;

    // // assume size of indecies will be the same or 0 for now
    // for (unsigned int i = 0; i < vector_indecies.size(); i++) {
    //     if (uv_indices.size() < 1) { // pull this if out
    //         unsigned int norm_index = noramal_indecies[i];
    //         unsigned int vector_index = vector_indecies[i];

    //         glm::vec3 norm = temp_norms[norm_index-1];
    //         glm::vec3 vector = temp_verts[vector_index-1];
    //         glm::vec2 empty_tex;

    //         Vertex vertex;
    //         vertex.Normal = norm;
    //         vertex.Position = vector;
    //         vertex.TexCoords = empty_tex;
    //     } else {
    //         // TODO case when there is a texture
    //     }

    // }

    // indecies.insert(indecies.end(), vector_indecies.begin(), vector_indecies.end());
    // indecies.insert(indecies.end(), noramal_indecies.begin(), noramal_indecies.end());
    // indecies.insert(indecies.end(), uv_indices.begin(), uv_indices.end());

    return thing;
}