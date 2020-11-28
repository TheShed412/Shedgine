#include "SimpleCross.hpp"

using namespace Game;
using namespace Crosshairs;

SimpleCross::SimpleCross(int width, int height) {
    this->screenHeight = height;
    this->screenWidth = width;
    this->projection = glm::ortho(
        0.0f,
        static_cast<float>(width),
        static_cast<float>(height),
        0.0f,
        0.0f,
        100.0f
    );
}

SimpleCross::~SimpleCross(){

}

// TODO: find out what I can pull out in to a parent function
void SimpleCross::Create() {
    ctm = glm::mat4(1.0);
    model_view = glm::mat4(1.0); // just so it is not null
    GLuint vao;
    GLuint vbo;
 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices = makeCrosshair();
    
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
 
    //here we assign the values
    this->vao = vao;
    this->vbos.push_back(vbo);
}

// TODO: need to pull this out to a parent
void SimpleCross::Update() {
    // model_view = camera->getModelView();
}

void SimpleCross::Draw() {
    glUseProgram(program);
    glBindVertexArray(vao);
    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    glDrawArrays(GL_LINES, 0, vectors);
}

void SimpleCross::processKeyboard(Movement direction, float deltaTime) {
    
}

std::vector<VertexFormat> SimpleCross::makeCrosshair() {
    std::vector<VertexFormat> vertices;
    glm::vec4 red = glm::vec4(0.9, 0.3, 0.3, 1);


    vertices.push_back(VertexFormat(glm::vec3((screenWidth/2), (screenHeight/2) + 7.0, 0.0), red));
    vertices.push_back(VertexFormat(glm::vec3((screenWidth/2), (screenHeight/2) - 7.0, 0.0), red));

    vertices.push_back(VertexFormat(glm::vec3((screenWidth/2) + 7.0, (screenHeight/2), 0.0), red));
    vertices.push_back(VertexFormat(glm::vec3((screenWidth/2) - 7.0, (screenHeight/2), 0.0), red));
    
    vectors = vertices.size();
    return vertices;
}