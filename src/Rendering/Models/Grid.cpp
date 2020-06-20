#include "Grid.hpp"
#include "../Camera.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

using namespace Rendering;
using namespace Models;

// TODO: make this able to be whatever size
Grid::Grid() {

}

Grid::~Grid(){

}

// TODO: find out what I can pull out in to a parent function
void Grid::Create() {
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
void Grid::Update() {
    model_view = camera->getModelView();
}

void Grid::Draw() {
    glUseProgram(program);
    glBindVertexArray(vao);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    glDrawArrays(GL_LINES, 0, vectors);
}

void Grid::processKeyboard(Movement direction, float deltaTime) {
    
}

std::vector<VertexFormat> Grid::makeGrid() {
    std::vector<VertexFormat> vertices;
    glm::vec4 color;

    for(int i=0;i<=10;i++) {// TODO: i'd chagne this to change how big the grid is
        if(i == 0) {
            color = glm::vec4(0.3, 0.3, 0.6, 1);
        } else {
            color = glm::vec4(0.25, 0.25, 0.25, 1);
        }
        vertices.push_back(VertexFormat(glm::vec3(i, 0.0, 0.0), color));
        vertices.push_back(VertexFormat(glm::vec3(i, 0.0, 10.0), color));
        vertices.push_back(VertexFormat(glm::vec3(0.0, 0.0, i), color));
        vertices.push_back(VertexFormat(glm::vec3(10.0, 0.0, i), color));
    }
    
    vectors = vertices.size();
    return vertices;
}