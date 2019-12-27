#include "Torus.hpp"

using namespace Rendering;
using namespace Models;
 
Torus::Torus()
{
}
 
Torus::~Torus()
{
 //is going to be deleted in Models.cpp (inheritance)
}
 
void Torus::Create()
{
    std::cout << "In torus now" << std::endl;
    GLuint vao;
    GLuint vbo;
 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(glm::vec3(0.10, -0.10, 0.0),
        glm::vec4(1, 0, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-0.10, -0.10, 0.0),
        glm::vec4(0, 1, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(0.10, 0.10, 0.0),
        glm::vec4(0, 0, 1, 1)));
 
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
                           (void*)0);
    glEnableVertexAttribArray(1);
        // you can use offsetof to get the offset of an attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
                           (void*)(offsetof(VertexFormat, VertexFormat::color)));
    glBindVertexArray(0);
 
        //here we assign the values
    this->vao = vao;
    this->vbos.push_back(vbo);
}
 
void Torus::Update()
{
  //for triangle there is nothing to update for now
}
 
void Torus::Draw()
{
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}