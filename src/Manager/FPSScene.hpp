#pragma once
#include "SceneManager.hpp"
#include "ModelsManager.hpp"
#include <btBulletDynamicsCommon.h>

namespace Managers
{
  class FPSScene : public SceneManager
  {
    private:
      // Physics collision setup
      btDiscreteDynamicsWorld* dynamicsWorld;
      btAlignedObjectArray<btCollisionShape*> collisionShapes;
      btSequentialImpulseConstraintSolver* solver;
      btBroadphaseInterface* overlappingPairCache;
      btCollisionDispatcher* dispatcher;
      btDefaultCollisionConfiguration* collisionConfiguration;

      bool firstMouse = true;
      float lastX;
      float lastY;
      void setupCollisions();
    public:
      FPSScene();
      FPSScene(Core::WindowInfo);
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