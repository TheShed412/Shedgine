#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Core/Init/InitSDL.hpp"
#include "Core/Init/InitGLUT.hpp"

#include "Manager/ShaderManager.hpp"
#include "Manager/SceneManager.hpp"
#include "Manager/DebugScene.hpp"
#include "Manager/FPSScene.hpp"


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

    Core::WindowInfo window(std::string("Shedgine"),
                            400, 200,//position
                            width, height, //size
                            true);//reshape
    
    Core::ContextInfo context(4, 5, true);
    Core::FramebufferInfo frameBufferInfo(true, true, true, true);
    

    if( argc > 1 && strcmp(argv[1], "modelView") == 0) {
        Core::Init::InitGLUT::init(window, context, frameBufferInfo);
        std::cout << "MODEL VIEW SCENE" << std::endl;
        Core::IListener* debugScene = new Managers::DebugScene();
        Core::Init::InitGLUT::setListener(debugScene);
        Core::Init::InitGLUT::run();
    } else if ( argc > 1 && strcmp(argv[1], "fps") == 0) {
        Core::Init::InitGLUT::init(window, context, frameBufferInfo);
        std::cout << "GAME SCENE" << std::endl;
        Core::IListener* scene = new Managers::FPSScene(window);
        Core::Init::InitGLUT::setListener(scene);
        Core::Init::InitGLUT::run();
    } else if ( argc > 1 && strcmp(argv[1], "sdl") == 0) {
        Core::Init::InitSDL::init(window, context, frameBufferInfo);
        std::cout << "SDL SCENE" << std::endl;
        Core::Init::InitSDL::run();
    } else {
        Core::Init::InitGLUT::init(window, context, frameBufferInfo);
        std::cout << "GAME SCENE" << std::endl;
        Core::IListener* scene = new Managers::SceneManager();
        Core::Init::InitGLUT::setListener(scene);
        Core::Init::InitGLUT::run();
    }
    
    
    return 0;
}