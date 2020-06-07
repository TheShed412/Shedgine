#include "Redical.hpp"
#include "../Camera.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

using namespace Rendering;
using namespace Models;

// TODO: make this able to be whatever size
Redical::Redical() {

}

Redical::~Redical(){

}

// TODO: find out what I can pull out in to a parent function
void Redical::Create() {
    ctm = glm::mat4(1.0);
    GLuint vao;
    GLuint vbo;
 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices = makeGrid();
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vectors, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),(void*)0);
    glEnableVertexAttribArray(1);
        // you can use offsetof to get the offset of an attribute
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

// TODO: need to pull this out to a parent
void Redical::Update() {
    model_view = camera->getModelView();
}

void Redical::Draw() {
    glUseProgram(program);
    glBindVertexArray(vao);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    glDrawArrays(GL_LINES, 0, vectors);
}

void Redical::processKeyboard(Movement direction, float deltaTime) {
    
}

std::vector<VertexFormat> Redical::makeGrid() {
    std::vector<VertexFormat> vertices;
    glm::vec4 color;

    color = glm::vec4(0.3, 0.3, 0.6, 1);
    vertices.push_back(VertexFormat(glm::vec3(-0.5, -0.5, -5.0), color));
    vertices.push_back(VertexFormat(glm::vec3(-0.5, 0.5, -5.0), color));
    vertices.push_back(VertexFormat(glm::vec3(-0.5, -0.5, -5.0), color));
    vertices.push_back(VertexFormat(glm::vec3(0.5, -0.5, -5.0), color));

    vertices.push_back(VertexFormat(glm::vec3(0.5, 0.5, -5.0), color));
    vertices.push_back(VertexFormat(glm::vec3(-0.5, 0.5, -5.0), color));
    vertices.push_back(VertexFormat(glm::vec3(0.5, 0.5, -5.0), color));
    vertices.push_back(VertexFormat(glm::vec3(0.5, -0.5, -5.0), color));

    vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, -7.0), color));
    vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.25, -7.0), color));
    vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, -7.0), color));
    vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, -7.0), color));

    vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, -7.0), color));
    vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.25, -7.0), color));
    vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, -7.0), color));
    vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, -7.0), color));
    
    vectors = vertices.size();
    return vertices;
}