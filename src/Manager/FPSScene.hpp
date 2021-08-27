#pragma once
#include "ModelsManager.hpp"
#include "TextureManager.hpp"
#include "../Core/Game/Manager/ActorManager.hpp"
#include "../Core/Game/Input/InputHandler.hpp"
#include "../Core/Game/Manager/ObjectManager.hpp"
#include "../Core/Init/WindowInfo.hpp"
#include "../Core/EventManager.hpp"
#include "../Core/Init/IListener.hpp"

#include <SDL2/SDL.h>

using namespace Graphics::Managers;
using namespace Game::Managers;

namespace Graphics {
  namespace Managers
  {
    class FPSScene : public Core::IListener {
      private:
        SDL_Window* sdlWindow;
        Input::InputHandler* inputHandler;

        bool firstMouse = true;
        float lastX;
        float lastY;
        void setupCollisions();
        void addToScene(Rendering::Models::LoadedObject*, std::string, std::string);
        void addToScene(Game::Actor*, std::vector<VertexFormat>, std::string, std::string);
        void castRays();
        //void collisionCheck(btDynamicsWorld *dynamicsWorld, btScalar timeStep);
      public:
        FPSScene();
        FPSScene(Core::WindowInfo);
        ~FPSScene();
        void notifyBeginFrame() override;
        void notifyDisplayFrame() override;
        void notifyKeyboardInput(unsigned char key, bool pressed) override;
        void notifyKeyboardUp(SDL_Keysym key) override;
        void notifyMouseInput(int button, int state, int x, int y) override;
        void notifyMouseMovementInput(int x, int y) override;
        void notifyEndFrame() override;
        void notifyReshape(int width,
                                  int height,
                                  int previous_width,
                                  int previous_height) override;

      protected:
        Managers::TextureManager* textureManager;
        Managers::ShaderManager* shader_manager;
        Managers::ModelsManager* models_manager;
        Shed::EventManager* eventManager;
        Rendering::TextureLoader* textureLoader;
        Rendering::Light* light;
        Rendering::Camera* camera;
        Game::Managers::ObjectManager* gameObjectManager;
        Game::Managers::ActorManager* actorManager;
        glm::mat4 projection;
        Core::WindowInfo windowInfo;

  };
  }
}