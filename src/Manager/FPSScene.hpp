#pragma once
#include "SceneManager.hpp"
#include "ModelsManager.hpp"
#include "../Core/Physics/PhysicsObject.hpp"
#include "../Core/Physics/Debugger/GLDebugDrawer.hpp"

#include <btBulletDynamicsCommon.h>
#include <LinearMath/btIDebugDraw.h>

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
      GLDebugDrawer* debugDrawer;
      // TODO: once it is all figured out, seperate this to a manager
      // update could get pretty complicated with physics objects
      // it will also more modularize the code in one place
      std::map<std::string, Physics::PhysicsObject*> physicsObjects;

      bool firstMouse = true;
      float lastX;
      float lastY;
      void setupCollisions();
      void addToScene(Rendering::Models::LoadedObject*, std::string, std::string);
      void addToScene(Game::Actor*, std::vector<VertexFormat>, std::string, std::string);
      void addToScene(Physics::PhysicsObject*, std::vector<VertexFormat>, std::string, std::string);
      //void collisionCheck(btDynamicsWorld *dynamicsWorld, btScalar timeStep);
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