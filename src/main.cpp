#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Core/Init/InitSDL.hpp"

#include "Manager/ShaderManager.hpp"
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

    Core::WindowInfo window(std::string("Hell Itself"),
                            400, 200,//position
                            width, height, //size
                            true);//reshape
    
    Core::ContextInfo context(4, 5, true);
    

    Core::Init::InitSDL::init(window, context);
    Core::IListener* scene = new Graphics::Managers::FPSScene(window);
    std::cout << "SDL SCENE" << std::endl;
    Core::Init::InitSDL::setListener(scene);
    Core::Init::InitSDL::run();
    
    return 0;
}