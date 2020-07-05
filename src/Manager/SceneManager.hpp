#pragma once
#include "ShaderManager.hpp"
#include "ModelsManager.hpp"
#include "../Rendering/Camera.hpp"
#include "../Rendering/Light.hpp"
#include "../Rendering/Texture/TextureLoader.hpp"
#include "../Core/Init/IListener.hpp"
#include "../Core/Init/WindowInfo.hpp"
#include "../Core/Game/GameObject.hpp"
#include "../Core/Game/Manager/ObjectManager.hpp"
#include "../Core/Game/Manager/ActorManager.hpp"

namespace Managers
{
  class SceneManager : public Core::IListener
  {
    public:
      SceneManager();
      SceneManager(Core::WindowInfo);
      ~SceneManager();
 
      virtual void notifyBeginFrame();
      virtual void notifyDisplayFrame();
      virtual void notifyKeyboardInput(unsigned char key);
      virtual void notifyMouseInput(int button, int state, int x, int y);
      virtual void notifyMouseMovementInput(int x, int y);
      virtual void notifyKeyboardUp(unsigned char key);
      virtual void notifyEndFrame();
      virtual void notifyReshape(int width,
                                 int height,
                                 int previous_width,
                                 int previous_height);
    protected:
      Managers::ShaderManager* shader_manager;
      Managers::ModelsManager* models_manager;
      Rendering::TextureLoader* textureLoader;
      Rendering::Light* light;
      Rendering::Camera* camera;
      Game::Managers::ObjectManager* gameObjectManager;
      Game::Managers::ActorManager* actorManager;
      glm::mat4 projection;
      Core::WindowInfo windowInfo;

 };
}