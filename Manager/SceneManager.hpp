#pragma once
#include "ShaderManager.hpp"
#include "ModelsManager.hpp"
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
      virtual void notifyEndFrame();
      virtual void notifyReshape(int width,
                                 int height,
                                 int previous_width,
                                 int previous_height);
    private:
      Managers::ShaderManager* shader_manager;
      Managers::ModelsManager* models_manager;
 };
}