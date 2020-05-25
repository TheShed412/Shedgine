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
    GLuint ibo;
 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices = makeCube(0.25);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vectors, &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

    glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));
    
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
    model_view = camera->getModelView();
}
 
void Cube::Draw(Light light)
{
    glUseProgram(program);
	glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->GetTexture("crate"));
    unsigned int textureLocation = glGetUniformLocation(program, "texture1");
    glUniform1i(textureLocation, 0);
    glBindVertexArray(vao);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    glDrawArrays(GL_TRIANGLES, 0, vectors);
}

void Cube::processKeyboard(Movement direction, float deltaTime) {
    
}

std::vector<VertexFormat> Cube::makeCube(GLfloat size) {
    std::vector<VertexFormat> vertices;

    // FRONT FACE
    vertices.push_back(VertexFormat(glm::vec3(size, -size, 0.0),
        glm::vec2(0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0),
        glm::vec2(0, 0)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, 0.0),
        glm::vec2(1, 1)));
    

    vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0),
        glm::vec2(1, 0)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, 0.0),
        glm::vec2(1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0),
        glm::vec2(0, 0)));
    

    // BACK FACE
    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec2(0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, -size*2),
        glm::vec2(0, 0)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, -size*2),
        glm::vec2(1, 1)));

    vertices.push_back(VertexFormat(glm::vec3(-size, -size, -size*2),
        glm::vec2(1, 0)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec2(1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, size, -size*2),
        glm::vec2(0, 0)));


    // TOP FACE
    vertices.push_back(VertexFormat(glm::vec3(-size, size, -size*2),
        glm::vec2(0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec2(0, 0)));
    vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0),
        glm::vec2(1, 1)));

    vertices.push_back(VertexFormat(glm::vec3(size, size, 0.0),
        glm::vec2(1, 0)));
    vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0),
        glm::vec2(1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec2(0, 0)));

    // BOTTOM FACE
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0),
        glm::vec2(0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, -size*2),
        glm::vec2(0, 0)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, -size*2),
        glm::vec2(1, 1)));

    vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0),
        glm::vec2(1, 0)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, 0.0),
        glm::vec2(1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, -size*2),
        glm::vec2(0, 0)));

    // RIGHT FACE
    vertices.push_back(VertexFormat(glm::vec3(-size, size, -size*2),
        glm::vec2(0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0),
        glm::vec2(0, 0)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, -size*2),
        glm::vec2(1, 1)));

    vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0),
        glm::vec2(1, 0)));
    vertices.push_back(VertexFormat(glm::vec3(-size, -size, -size*2),
        glm::vec2(1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0),
        glm::vec2(0, 0)));

    // LEFT FACE
    vertices.push_back(VertexFormat(glm::vec3(size, size, 0.0),
        glm::vec2(0, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec2(0, 0)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, 0.0),
        glm::vec2(1, 1)));

    vertices.push_back(VertexFormat(glm::vec3(size, size, -size*2),
        glm::vec2(1, 0)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, -size*2),
        glm::vec2(1, 1)));
    vertices.push_back(VertexFormat(glm::vec3(size, -size, 0.0),
        glm::vec2(0, 0)));
    
    vectors = vertices.size();
    
    return vertices;
}