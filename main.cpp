#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include<fstream>
#include<vector>

#include "Core/ShaderLoader.hpp"
#include "Core/GameModels.hpp"

using namespace Core;

Models::GameModels* gameModels;
GLuint program;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(gameModels->GetModel("triangle1"));
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
 
    glutSwapBuffers();
}

void closeCallback()
{
 
    std::cout << "GLUT:\t Finished" << std::endl;
    glutLeaveMainLoop();
}

void init() 
{
    glEnable(GL_DEPTH_TEST);

    gameModels = new Models::GameModels();
    gameModels->CreateTriangleModel("triangle1");
 
    //load and compile shaders
    ShaderLoader shaderLoader;
    program = shaderLoader.CreateProgram("shaders/vertex_shader.glsl",
                                         "shaders/fragment_shader.glsl");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor(1.0, 0.0, 0.0, 1.0);//clear red
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(500, 500);//optional
    glutInitWindowSize(800, 600); //optional
    glutCreateWindow("Lol not my first window");
    glewInit();
    init();
 
    // register callbacks
    glutDisplayFunc(renderScene);
    glutCloseFunc(closeCallback);
    glutMainLoop();

    delete gameModels;
    glDeleteProgram(program);
    return 0;
}