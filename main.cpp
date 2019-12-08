#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include<fstream>
#include<vector>

#include "Core/ShaderLoader.hpp"

using namespace Core;
 
GLuint program;

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //use the created program
    glUseProgram(program);
 
    //draw 3 vertices as triangles
    glDrawArrays(GL_TRIANGLES, 0, 3);
 
    glutSwapBuffers();
}

void init() 
{
    glEnable(GL_DEPTH_TEST);
 
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
    glutMainLoop();
    glDeleteProgram(program);
    return 0;
}