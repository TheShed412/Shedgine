#include "InitSDL.hpp"

using namespace Core::Init;

Core::IListener* InitSDL::listener = NULL;
Core::WindowInfo InitSDL::windowInformation;
SDL_Window* InitSDL::sdlWindow = NULL;
bool InitSDL::quit = false;

void InitSDL::init(const Core::WindowInfo& windowInfo,
                     const Core::ContextInfo& contextInfo,
                     const Core::FramebufferInfo& framebufferInfo)
{
    int bpp = 0;
    int flags = 0;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "::SDL INIT ERROR::" << std::endl;
        exit(EXIT_FAILURE);
    }

    int width = windowInfo.width;
    int height = windowInfo.height;
    
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    sdlWindow = SDL_CreateWindow(
        windowInfo.name.c_str(),
        windowInfo.position_x,
        windowInfo.position_y,
        windowInfo.width,
        windowInfo.height,
        flags
    );

    if (sdlWindow == NULL) {
        std::cerr << "::SDL WINDOW CREATION ERROR::" << std::endl;
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEBUG_OUTPUT);
}

void InitSDL::run() {
    while(!quit) {
        SDL_Event event;
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                // Break out of the loop on quit
                quit = true;
            }
        }
    }
    close();
}

void InitSDL::close() {
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}
void InitSDL::setListener(Core::IListener*& iListener) {}
 
void InitSDL::enterFullscreen() {}
void InitSDL::exitFullscreen() {}

void InitSDL::idleCallback(void) {}
void InitSDL::displayCallback(void){}
void InitSDL::reshapeCallback(int width, int height){}
void InitSDL::keyboardCallback(unsigned char key, int mousex, int mousey){}
void InitSDL::mouseCallback(int button, int state, int x, int y){}
void InitSDL::mouseMovementCallback(int x, int y){}
void InitSDL::closeCallback(){}
void InitSDL::keyboardUp(unsigned char key, int x, int y){}