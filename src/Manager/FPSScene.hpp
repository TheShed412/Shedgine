#pragma once
#include "SceneManager.hpp"
#include "ModelsManager.hpp"

namespace Managers
{
  class FPSScene : public SceneManager
  {
    private:
      bool firstMouse = true;
      float lastX;
      float lastY;
    public:
      FPSScene();
      ~FPSScene();
      void notifyBeginFrame() override;
      void notifyDisplayFrame() override;
      void notifyKeyboardInput(unsigned char key) override;
      void notifyMouseInput(int button, int state, int x, int y) override;
      void notifyMouseMovementInput(int x, int y) override;
      void notifyKeyboardUp(unsigned char key) override;
      void notifyEndFrame() override;
      void notifyReshape(int width,
                                 int height,
                                 int previous_width,
                                 int previous_height) override;

 };
}