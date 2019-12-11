#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Core/Init/InitGLUT.hpp"

#include "Core/ShaderLoader.hpp"
#include "Core/GameModels.hpp"

#include "Manager/ShaderManager.hpp"
#include "Manager/SceneManager.hpp"

using namespace Core;
using namespace Init;

Managers::ShaderManager* shaderManager;

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

    shaderManager = new Managers::ShaderManager();
    shaderManager->CreateProgram("colorShader",
                                "shaders/vertex_shader.glsl",
                                "shaders/fragment_shader.glsl");
    program = shaderManager->GetShader("colorShader");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor(1.0, 0.0, 0.0, 1.0);//clear red
}

int main(int argc, char **argv)
{
    WindowInfo window(std::string("in2gpu OpenGL Beginner Tutorial "),
                            400, 200,//position
                            800, 600, //size
                            true);//reshape
    
    ContextInfo context(4, 5, true);
    FramebufferInfo frameBufferInfo(true, true, true, true);
    InitGLUT::init(window, context, frameBufferInfo);
    IListener* scene = new Managers::SceneManager();
    InitGLUT::setListener(scene);
    
    InitGLUT::run();
    return 0;
}