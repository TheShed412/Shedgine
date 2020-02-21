#include "Cube.hpp"
#include "../Camera.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

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
    ctm = glm::mat4(1.0);
    GLuint vao;
    GLuint vbo;
 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices = makeCube(0.25);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vectors, &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));

    glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
    
    glBindVertexArray(0);

    ctm_location = glGetUniformLocation(program, "ctm");
    projection_location = glGetUniformLocation(program, "projection");
    model_view_location = glGetUniformLocation(program, "modelView");
 
    //here we assign the values
    this->vao = vao;
    this->vbos.push_back(vbo);
}
 
void Cube::Update()
{
    //for triangle there is nothing to update for now
    model_view = camera->getModelView();
    //ctm = glm::rotate(ctm, glm::radians(1.0f), glm::vec3(1,1,0));
}
 
void Cube::Draw()
{
    glUseProgram(program);
	glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->GetTexture("Create"));
    unsigned int textureLocation = glGetUniformLocation(program, "texture1");
    glUniform1i(textureLocation, 0);
    glUseProgram(program);
    glBindVertexArray(vao);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    glDrawArrays(GL_TRIANGLES, 0, vectors);
}

std::vector<VertexFormat> Cube::makeCube(GLfloat size) {
    std::vector<VertexFormat> vertices;

    // FRONT FACE
    vertices.push_back(VertexFormat(glm::vec3(size, -size, 0.0),
        glm::vec4(1, 0, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0),
        glm::vec4(1, 0, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, 0.0),
        glm::vec4(1, 0, 0, 1)));
    

    vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0),
        glm::vec4(0, 1, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, 0.0),
        glm::vec4(0, 1, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0),
        glm::vec4(0, 1, 0, 1)));
    

    // BACK FACE
    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec4(1, 1, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, -size*2),
        glm::vec4(1, 1, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, -size*2),
        glm::vec4(1, 1, 0, 1)));

    vertices.push_back(VertexFormat(glm::vec3(-size, -size, -size*2),
        glm::vec4(0, 0, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec4(0, 0, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, size, -size*2),
        glm::vec4(0, 0, 1, 1)));


    // TOP FACE
    vertices.push_back(VertexFormat(glm::vec3(-size, size, -size*2),
        glm::vec4(1, 0, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec4(1, 0, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0),
        glm::vec4(1, 0, 1, 1)));

    vertices.push_back(VertexFormat(glm::vec3(size, size, 0.0),
        glm::vec4(0, 1, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0),
        glm::vec4(0, 1, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec4(0, 1, 1, 1)));

    // BOTTOM FACE
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0),
        glm::vec4(1, 0, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, -size*2),
        glm::vec4(1, 0, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, -size*2),
        glm::vec4(1, 0, 1, 1)));

    vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0),
        glm::vec4(0, 1, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, 0.0),
        glm::vec4(0, 1, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, -size*2),
        glm::vec4(0, 1, 0, 1)));

    // RIGHT FACE
    vertices.push_back(VertexFormat(glm::vec3(-size, size, -size*2),
        glm::vec4(1, 0, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0),
        glm::vec4(1, 0, 0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, -size*2),
        glm::vec4(1, 0, 0, 1)));

    vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0),
        glm::vec4(0, 1, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, -size*2),
        glm::vec4(0, 1, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0),
        glm::vec4(0, 1, 1, 1)));

    // LEFT FACE
    vertices.push_back(VertexFormat(glm::vec3(size, size, 0.0),
        glm::vec4(1, 0, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec4(1, 0, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, 0.0),
        glm::vec4(1, 0, 1, 1)));

    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec4(0, 1, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, -size*2),
        glm::vec4(0, 1, 1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, 0.0),
        glm::vec4(0, 1, 1, 1)));
    
    vectors = vertices.size();
    
    return vertices;
}