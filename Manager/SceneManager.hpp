#pragma once
#include "ShaderManager.hpp"
#include "ModelsManager.hpp"
#include "../Rendering/Camera.hpp"
#include "../Core/Init/IListener.hpp"

namespace Managers
{
  class SceneManager : public Core::IListener
  {
    public:
      SceneManager();
      ~SceneManager();
 
      virtual void notifyBeginFrame();
      virtual void notifyDisplayFrame();
      virtual void notifyKeyboardInput(unsigned char key);
      virtual void notifyMouseInput(int button, int state, int x, int y);
      virtual void notifyMouseMovementInput(int x, int y);
      virtual void notifyEndFrame();
      virtual void notifyReshape(int width,
                                 int height,
                                 int previous_width,
                                 int previous_height);
    private:
      Managers::ShaderManager* shader_manager;
      Managers::ModelsManager* models_manager;
      Rendering::Camera* camera;
 };
}