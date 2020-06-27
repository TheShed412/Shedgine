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
  };
 
  inline IListener::~IListener(){
     //implementation of pure virtual destructor
  }
}