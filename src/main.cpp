#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Core/Init/InitGLUT.hpp"

#include "Manager/ShaderManager.hpp"
#include "Manager/SceneManager.hpp"
#include "Manager/DebugScene.hpp"
#include "Manager/FPSScene.hpp"

using namespace Core;
using namespace Init;

GLuint program;

int main(int argc, char **argv)
{
    // TODO: make the window size variable at least between my development machines
    char* windowWidth = std::getenv("SHED_W");
    char* windowHeight = std::getenv("SHED_H");
    int width = 1200;
    int height = 800;

    try {
        if (windowWidth) {
            width = stoi(windowWidth);
        }
        if (windowHeight) {
            height = stoi(windowHeight);
        }
    } catch (...) {
        std::cerr << "WIDTH OR HEIGHT NOT A NUMBER" << std::endl;
        std::cerr << "WIDTH: " << windowWidth << " HEIGHT: " << windowHeight << std::endl;
    }

    WindowInfo window(std::string("Shedgine"),
                            400, 200,//position
                            width, height, //size
                            true);//reshape
    
    ContextInfo context(4, 5, true);
    FramebufferInfo frameBufferInfo(true, true, true, true);
    InitGLUT::init(window, context, frameBufferInfo);

    if( argc > 1 && strcmp(argv[1], "modelView") == 0) {
        std::cout << "MODEL VIEW SCENE" << std::endl;
        IListener* debugScene = new Managers::DebugScene();
        InitGLUT::setListener(debugScene);
    } else if ( argc > 1 && strcmp(argv[1], "fps") == 0) {
        std::cout << "GAME SCENE" << std::endl;
        IListener* scene = new Managers::FPSScene(window);
        InitGLUT::setListener(scene);
    } else {
        std::cout << "GAME SCENE" << std::endl;
        IListener* scene = new Managers::SceneManager();
        InitGLUT::setListener(scene);
    }
    
    InitGLUT::run();
    return 0;
}