#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Core/Init/InitGLUT.hpp"

#include "Manager/ShaderManager.hpp"
#include "Manager/SceneManager.hpp"

using namespace Core;
using namespace Init;

GLuint program;

int main(int argc, char **argv)
{
    WindowInfo window(std::string("Project Reimplimentations"),
                            400, 200,//position
                            1600, 1200, //size
                            true);//reshape
    
    ContextInfo context(4, 5, true);
    FramebufferInfo frameBufferInfo(true, true, true, true);
    InitGLUT::init(window, context, frameBufferInfo);
    IListener* scene = new Managers::SceneManager();
    InitGLUT::setListener(scene);
    
    InitGLUT::run();
    return 0;
}