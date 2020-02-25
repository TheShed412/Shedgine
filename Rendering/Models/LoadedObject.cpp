#include "LoadedObject.hpp"
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