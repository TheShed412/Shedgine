#include "LoadedObject.hpp"
#include "../ObjectLoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../../Core/stb_image.h"

#include <deque>
#include <algorithm>

/**
 * I need to add the ability to add mtl from objs here. 
 * http://www.programmersought.com/article/5130383977/
 * 
 * I need to taking the specular, ambient, diffuse light, and color from the mtl file.
 * I will also need new accompanying shader file to consume the light values properly. 
*/

using namespace Rendering;
using namespace Models;

LoadedObject::LoadedObject() {}
LoadedObject::~LoadedObject() {}

LoadedObject::LoadedObject(std::string filename) {
    this->filename = filename;
}
 
void LoadedObject::Create(){
    ctm = glm::mat4(1.0);

    ctm_location = glGetUniformLocation(program, "ctm");
    projection_location = glGetUniformLocation(program, "projection");
    model_view_location = glGetUniformLocation(program, "modelView");

    loadObject();
}

void LoadedObject::processKeyboard(Movement direction, float deltaTime) {
    switch (direction)
    {
        case FORWARD:
            ctm = glm::translate(ctm, {0, 0, -0.1});
            break;
        case BACKWARD:
            ctm = glm::translate(ctm, {0, 0, 0.1});
            break;
        case LEFT:
            ctm = glm::translate(ctm, {-0.1, 0, 0});
            break;
        case RIGHT:
            ctm = glm::translate(ctm, {0.1, 0, 0});
            break;
        
        default:
            break;
    }
}

void LoadedObject::Update(){
    model_view = camera->getModelView();
    //ctm = glm::translate(ctm, {0.1, 0, 0});
}

void LoadedObject::Draw(){
    // glUseProgram(program);
	// glBindVertexArray(vao);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, this->GetTexture("crate"));
    // unsigned int textureLocation = glGetUniformLocation(program, "texture1");
    // glUniform1i(textureLocation, 0);
    // glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
    // glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    // glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    // glDrawArrays(GL_TRIANGLES, 0, vectors);
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(program,ctm_location, projection_location, model_view_location, ctm, projection, model_view);
    }
    
}

std::vector<VertexFormat> LoadedObject::makeObject() {
    ObjectLoader* objLoader = new ObjectLoader();
    std::vector<VertexFormat> vertecies = objLoader->LoadObject(filename);
    vectors = vertecies.size();
    return vertecies;
}

void LoadedObject::processNode(aiNode *node, const aiScene *scene) {
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

std::vector<TextureFormat> LoadedObject::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<TextureFormat> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < textures.size(); j++) {
            if(std::strcmp(textures[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(textures[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            TextureFormat texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

unsigned int LoadedObject::TextureFromFile(const char *path, const std::string &directory) {
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

Mesh LoadedObject::processMesh(aiMesh *mesh, const aiScene *scene) {
    // data to fill
    std::vector<VertexFormat> vertices;
    std::deque<unsigned int> indices;
    std::vector<TextureFormat> textures;

    // Walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        VertexFormat vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if(mesh->mNormals) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if(mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texture = vec;
        } else {
            vertex.texture = glm::vec2(0.0f, 0.0f);
        }
        // tangent
        if(mesh->mTangents) {
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;
        }
        // bitangent
        if(mesh->mBitangents) {
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitTangent = vector;
        }
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_front(face.mIndices[j]);
        }
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<TextureFormat> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<TextureFormat> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<TextureFormat> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<TextureFormat> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        
    // return a mesh object created from the extracted mesh data
    // std::reverse(vertices.begin(), vertices.end());
    // std::reverse(indices.begin(), indices.end());
    // std::reverse(textures.begin(), textures.end());
    return Mesh(vertices, {indices.begin(), indices.end()}, textures);
}

std::vector<VertexFormat> LoadedObject::loadObject() {
    std::vector<VertexFormat> vertecies;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        //return;
    }

    directory = filename.substr(0, filename.find_last_of('/'));

    processNode(scene->mRootNode, scene);

    return vertecies;
}