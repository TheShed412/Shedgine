#include "Cube.hpp"

using namespace Rendering;
using namespace Models;
 
Cube::Cube()
{
}
 
Cube::~Cube()
{
 //is going to be deleted in Models.cpp (inheritance)
}
 
void Cube::Create()
{
    GLuint vao;
    GLuint vbo;
 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices;
 
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 9002, &vertices[0], GL_STATIC_DRAW);
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
 
void Cube::Update()
{
  //for triangle there is nothing to update for now
}
 
void Cube::Draw()
{
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 9002);
}