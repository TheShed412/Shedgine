#pragma once

#include <iostream>

#include "ContextInfo.hpp"
#include "FrameBufferInfo.hpp"
#include "WindowInfo.hpp"
#include "InitGLEW.hpp"
#include "IListener.hpp"
 
namespace Core {
   namespace Init{//two namespaces
 
      class InitGLUT{
      private:
            static Core::IListener* listener;
            static Core::WindowInfo windowInformation;
 
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
            static void closeCallback();
      };
   }
}