#include "Mesh.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include<iostream>
using namespace Rendering;
using namespace Models;


Mesh::Mesh(){}

Mesh::Mesh(std::vector<VertexFormat> vertices, std::vector<unsigned int> indices, std::vector<TextureFormat> textures, Material mat, GLuint program) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->mat = mat;
    this->program = program;

    setupMesh();
}

void Mesh::setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenBuffers(1, &uniformBlockIndex);
        
        ctm_location = glGetUniformLocation(program, "ctm");
        projection_location = glGetUniformLocation(program, "projection");
        model_view_location = glGetUniformLocation(program, "modelView");
        ambient_location = glGetUniformLocation(program, "ambient");
        position_location = glGetUniformLocation(program, "position");
        specular_location = glGetUniformLocation(program, "specular");
        diffuse_location = glGetUniformLocation(program, "diffuse");
        constant_location = glGetUniformLocation(program, "constant");
        linear_location = glGetUniformLocation(program, "linear");
        quadratic_location = glGetUniformLocation(program, "quadratic");

        glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat) + sizeof(Material), &vertices[0], GL_DYNAMIC_DRAW);
        
        glBindBuffer(GL_UNIFORM_BUFFER, uniformBlockIndex);
        glBufferData(GL_UNIFORM_BUFFER,sizeof(Material),(void*)(&mat), GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);


        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, VertexFormat::normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, VertexFormat::texture));
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, VertexFormat::tangent));
        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, VertexFormat::bitTangent));

        glBindVertexArray(0);
}

void Mesh::Draw(glm::mat4 ctm,
                glm::mat4 projection,
                glm::mat4 model_view,
                Light* light) 
{
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;

    glUseProgram(program);

    for(unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if(name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if(name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(program, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }


    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *) &projection);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *) &model_view);
    glUniform3fv(ambient_location, 1, (GLfloat*) light->getAmbient());
    glUniform3fv(position_location, 1, (GLfloat*) light->getPosition());
    glUniform3fv(specular_location, 1, (GLfloat*) light->getSpecular());
    glUniform3fv(diffuse_location, 1, (GLfloat*) light->getDiffuse());
    glUniform1f(constant_location, light->getConstant());
    glUniform1f(linear_location, light->getLinear());
    glUniform1f(quadratic_location, light->getQuadratic());


    GLuint matIndex =  glGetUniformBlockIndex(program, "MatBlock");
    glUniformBlockBinding(program, matIndex, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBlockIndex);

    // draw mesh
    //GLuint lightIndex =  glGetUniformBlockIndex(program, "Light");
    
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBlockIndex);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Material), &this->mat);

    glBindVertexArray(VAO);
    //glBindBufferRange(GL_UNIFORM_BUFFER,0, uniformBlockIndex,0,sizeof(Material));
    //glBindBufferRange(GL_UNIFORM_BUFFER,lightIndex, lightObject,0,sizeof(sLight));
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

std::vector<VertexFormat> Mesh::getVertices() {
    return vertices;
}

std::vector<unsigned int> Mesh::getIndecies(){
    return indices;
}

std::vector<TextureFormat> Mesh::getTextures() {
    return textures;
}

unsigned int Mesh::getVAO(){
    return VAO;
}

unsigned int Mesh::getVBO(){
    return VBO;
}

unsigned int Mesh::getEBO(){
    return EBO;
}