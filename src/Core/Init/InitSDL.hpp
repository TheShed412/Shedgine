#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "ContextInfo.hpp"
#include "FrameBufferInfo.hpp"
#include "WindowInfo.hpp"
#include "InitGLEW.hpp"
#include "IListener.hpp"
#include "DebugOutput.hpp"
 
namespace Core {
   namespace Init{//two namespaces
 
      class InitSDL {
      private:
            static Core::IListener* listener;
            static Core::WindowInfo windowInformation;
            static SDL_Window* sdlWindow;
            static SDL_GLContext glContext;
            static bool quit;
 
       public:             //use the structures from Part II
         static void init(const Core::WindowInfo& window,
                          const Core::ContextInfo& context,
                          const Core::FramebufferInfo& framebufferInfo);
 
      public:
         static void run();//called from outside
         static void close();
         static void setListener(Core::IListener*& iListener);
 
         void enterFullscreen();
         void exitFullscreen();
 
         //used to print info about GL
         static void printOpenGLInfo(const Core::WindowInfo& windowInfo,
                                     const Core::ContextInfo& context);
      private:
            static void idleCallback(void);
            static void displayCallback(void);
            static void reshapeCallback(int width, int height);
            static void keyboardCallback(unsigned char key, int mousex, int mousey);
            static void mouseCallback(int button, int state, int x, int y);
            static void mouseMovementCallback(int x, int y);
            static void closeCallback();
            static void keyboardUp(unsigned char key, int x, int y);
      };
   }
}