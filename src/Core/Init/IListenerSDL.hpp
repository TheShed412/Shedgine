#pragma once

#include <SDL2/SDL.h>

#include "IListener.hpp"

namespace Core{
 
 class IListenerSDL : virtual public IListener
 {
    public:
      virtual ~IListenerSDL() = 0;
 
      //drawing functions
      virtual void notifyKeyboardInput(SDL_Keysym key) = 0;
      virtual void notifyKeyboardUp(SDL_Keysym key) = 0;
      virtual void notifyMouseInput(int button, int state, int x, int y) = 0;
      virtual void notifyMouseMovementInput(int x, int y) = 0;

    protected:
      bool sdlKeys[322] = {0};

      
  };
 
  inline IListenerSDL::~IListenerSDL(){
     //implementation of pure virtual destructor
  }
}