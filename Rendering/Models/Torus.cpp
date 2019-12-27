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
    GLuint vao;
    GLuint vbo;
 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices = makeTorus(0.5, 0.1, 300, 15, 0.05);
 
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
 
void Torus::Update()
{
  //for triangle there is nothing to update for now
}
 
void Torus::Draw()
{
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 9002);
}

std::vector<VertexFormat> Torus::makeTorus(GLfloat r, GLfloat sr, int n, int sn, GLfloat k) {
    std::vector<VertexFormat> torVector;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < (sn+1 * (i == n-1)); j++) {
            GLfloat a = 2*M_1_PI * (i+j/sn)/n;
            GLfloat a2 = 2*M_1_PI * (i+j/sn+k)/n;
            GLfloat sa = 2*M_1_PI * j/sn;

            GLfloat x1 = (r+sr*glm::cos(sa))*glm::cos(a);
            GLfloat y1 = (r+sr*glm::cos(sa))*glm::sin(a);
            GLfloat z1 = sr*glm::sin(sa);

            GLfloat x2 = (r+sr*glm::cos(sa))*glm::cos(a2);
            GLfloat y2 = (r+sr*glm::cos(sa))*glm::sin(a2);
            GLfloat z2 = sr*glm::sin(sa);

            torVector.push_back(VertexFormat(glm::vec3(x1, y1, z1),
                glm::vec4(1, 0, 0, 1)));

            torVector.push_back(VertexFormat(glm::vec3(x2, y2, z2),
                glm::vec4(1, 0, 0, 1)));
        }
    }

    return torVector;
}