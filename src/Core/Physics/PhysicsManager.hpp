#pragma once
#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <vector>

#include "../../Rendering/Camera.hpp"
#include "../../Rendering/Models/LoadedObject.hpp"
#include "../../Rendering/VertexFormat.hpp"
#include "Debugger/GLDebugDrawer.hpp"
#include "PhysicsObject.hpp"


/** 
 * This will be the wrapper class for physics operations. This will be a "singleton" loaded at the start of a scene
 * with any physics configurations that are loaded with the scene. Any scene level physics things should use this, or a 
 * child manager of this.
 * 
*/
namespace Physics
{
    struct btRayVectors {
        btVector3 start;
        btVector3 end;
    };
    class PhysicsManager {
        private:
            // Physics collision setup
            btDiscreteDynamicsWorld* dynamicsWorld;
            btAlignedObjectArray<btCollisionShape*> collisionShapes;
            btSequentialImpulseConstraintSolver* solver;
            btBroadphaseInterface* overlappingPairCache;
            btCollisionDispatcher* dispatcher;
            btDefaultCollisionConfiguration* collisionConfiguration;
            // TODO: I need to figure out how to get this to work
            GLDebugDrawer* debugDrawer;
            std::map<std::string, Physics::PhysicsObject*> physicsObjects;
            Physics::PhysicsObject* currPickedObject;
            int windowWidth;
            int windowHeight;
            int mouseButton;
            bool mouseButtonPressed;
            float gravity;
            int debugMode;
        public:
            PhysicsManager(int width, int height);
            PhysicsManager(int debugMode, float gravity, int width, int height);
            void endFrameProcess(Rendering::Camera* camera, int elapsedTime);
            void setupCollisions();
            void addPhysicsObject(std::string, PhysicsObject*);
            void setDebugMode(int);
            void setGravity(float);
            void setMouseState(int, bool);
            void pickObjects(Rendering::Camera* camera);
            void hitObject(Rendering::Camera* camera, float, float);
            PhysicsObject* detectObject(Rendering::Camera* camera, float);
    };
} // namespace Physics