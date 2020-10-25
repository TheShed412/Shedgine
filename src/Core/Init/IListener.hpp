#pragma once

#include <SDL2/SDL.h>

#include "IListener.hpp"

namespace Core{
 
 class IListener
 {
    public:
      virtual ~IListener() = 0;
 
      //drawing functions
      virtual void notifyBeginFrame() = 0;
      virtual void notifyDisplayFrame() = 0;
      virtual void notifyEndFrame() = 0;
      virtual void notifyKeyboardInput(unsigned char key, bool pressed) = 0;
      virtual void notifyKeyboardUp(SDL_Keysym key) = 0;
      virtual void notifyMouseInput(int button, int state, int x, int y) = 0;
      virtual void notifyMouseMovementInput(int x, int y) = 0;
      virtual void notifyReshape(int width,
                                  int height,
                                  int previous_width,
                                  int previous_height) = 0;

    protected:
      bool keys[322] = {0};
      int mouseBuffer;
      // This is a flag that I can check if I am in this buffer
      bool inBuffer;
      int previousTime;
      int elapsedTime;
      int currentTime;

      
  };
 
  inline IListener::~IListener(){
     //implementation of pure virtual destructor
  }
}