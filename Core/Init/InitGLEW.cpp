#include "InitGLEW.hpp"
using namespace Core;
using namespace Core::Init;
 
void Init_GLEW::Init(){
 
    glewExperimental = true;
    if (glewInit() == GLEW_OK)
    {
        std::cout << "GLEW: Initialize" << std::endl;
    }
    
    if (glewIsSupported("GL_VERSION_3_0"))
    {
        std::cout << "GLEW GL_VERSION_3_0 is 3.0\n ";
    }
    else
    {
        std::cout << " GLEW GL_VERSION_3_0 not supported\n ";
    }
}