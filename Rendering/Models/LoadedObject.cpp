#include "LoadedObject.hpp"
#include "../AssimpUtils.hpp"
#include "../ObjectLoader.hpp"

using namespace Rendering;
using namespace Models;

LoadedObject::LoadedObject() {}
LoadedObject::~LoadedObject() {}

LoadedObject::LoadedObject(std::string filename) {
    this->filename = filename;
}
 
void LoadedObject::Create(){
    ctm = glm::mat4(1.0);
    GLuint vao;
    GLuint vbo;
    GLuint ibo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices = makeObject();
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vectors, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
                           (void*)(offsetof(VertexFormat, VertexFormat::color)));
    
    glBindVertexArray(0);

    ctm_location = glGetUniformLocation(program, "ctm");
    projection_location = glGetUniformLocation(program, "projection");
    model_view_location = glGetUniformLocation(program, "modelView");
 
    //here we assign the values
    this->vao = vao;
    this->vbos.push_back(vbo);
}

void LoadedObject::Update(){
    model_view = camera->getModelView();
}

void LoadedObject::Draw(){
    glUseProgram(program);
	glBindVertexArray(vao);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, this->GetTexture("crate"));
    // unsigned int textureLocation = glGetUniformLocation(program, "texture1");
    // glUniform1i(textureLocation, 0);
    glBindVertexArray(vao);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    glDrawArrays(GL_TRIANGLES, 0, vectors);
}

std::vector<VertexFormat> LoadedObject::makeObject() {
    ObjectLoader* objLoader = new ObjectLoader();
    std::vector<VertexFormat> vertecies = objLoader->LoadObject(filename);
    vectors = vertecies.size();
    return vertecies;
}

void processNode(aiNode *node, const aiScene *scene)
{
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        //meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

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

    return vertecies;
}