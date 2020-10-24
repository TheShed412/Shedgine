#include "InitSDL.hpp"

using namespace Core::Init;

Core::IListener* InitSDL::listener = NULL;
Core::WindowInfo InitSDL::windowInformation;
SDL_Window* InitSDL::sdlWindow = NULL;
SDL_GLContext InitSDL::glContext = NULL;
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

    glContext = SDL_GL_CreateContext(sdlWindow);

    if (glContext == NULL) {
        std::cerr << "::SDL GL CONTEXT CREATION ERROR::" << std::endl;
        exit(EXIT_FAILURE);
    }

    Init::InitGLEW::Init();
    glDebugMessageCallback(DebugOutput::Callback, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                      GL_DONT_CARE, 0, NULL, GL_TRUE);

    printOpenGLInfo(windowInfo, contextInfo);
    glEnable(GL_DEBUG_OUTPUT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
        displayCallback();
    }
    close();
}

void InitSDL::close() {
    SDL_DestroyWindow(sdlWindow);
    SDL_GL_DeleteContext(glContext); 
    SDL_Quit();
}
 
void InitSDL::enterFullscreen() {}
void InitSDL::exitFullscreen() {}

void InitSDL::idleCallback(void) {}

void InitSDL::displayCallback(void) {
    if (listener){
        listener->notifyBeginFrame();
        listener->notifyDisplayFrame();
        glClearColor(1.f, 0.f, 1.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(sdlWindow);
   
        listener->notifyEndFrame();
    }
}

void InitSDL::reshapeCallback(int width, int height) {
    if (windowInformation.isReshapable == true) {
        if (listener){
            listener->notifyReshape(width,
                                 height,
                                 windowInformation.width,
                                 windowInformation.height);
        }
        windowInformation.width = width;
        windowInformation.height = height;
    }
}

void InitSDL::keyboardCallback(unsigned char key, int mousex, int mousey) {
    if(listener) {
        listener->notifyKeyboardInput(key);
    }
}

void InitSDL::mouseCallback(int button, int state, int x, int y) {
    if(listener) {
        listener->notifyMouseInput(button, state, x, y);
    }
}

void InitSDL::mouseMovementCallback(int x, int y) {
    if(listener) {
        listener->notifyMouseMovementInput(x, y);
    }
}

void InitSDL::closeCallback(){}
void InitSDL::keyboardUp(unsigned char key, int x, int y){}

void InitSDL::setListener(Core::IListener*& iListener)
{
   listener = iListener;
}

void InitSDL::printOpenGLInfo(const Core::WindowInfo& windowInfo,
                                const Core::ContextInfo& contextInfo){
 
    const unsigned char* renderer = glGetString(GL_RENDERER);
    const unsigned char* vendor = glGetString(GL_VENDOR);
    const unsigned char* version = glGetString(GL_VERSION);
    
    std::cout << "******************************************************************************" << std::endl;
    std::cout << "SDL:Initialise" << std::endl;
    std::cout << "SDL:\tVendor : " << vendor << std::endl;
    std::cout << "SDL:\tRenderer : " << renderer << std::endl;
    std::cout << "SDL:\tOpenGl version: " << version << std::endl;
}