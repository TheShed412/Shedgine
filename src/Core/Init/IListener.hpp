#pragma once
namespace Core{
 
 class IListener
 {
    public:
      virtual ~IListener() = 0;
 
      //drawing functions
      virtual void notifyBeginFrame() = 0;
      virtual void notifyDisplayFrame() = 0;
      virtual void notifyEndFrame() = 0;
      virtual void notifyKeyboardInput(unsigned char key) = 0;
      virtual void notifyKeyboardUp(unsigned char key) = 0;
      virtual void notifyMouseInput(int button, int state, int x, int y) = 0;
      virtual void notifyMouseMovementInput(int x, int y) = 0;
      virtual void notifyReshape(int width,
                                  int height,
                                  int previous_width,
                                  int previous_height) = 0;
    protected:
      unsigned char keys[255] = {0};
      // The mouseBuffer is the area from the outside of the screen where, if the mouse is in, it will be reset
      int mouseBuffer;
      // This is a flag that I can check if I am in this buffer
      bool inBuffer;
  };
 
  inline IListener::~IListener(){
     //implementation of pure virtual destructor
  }
}