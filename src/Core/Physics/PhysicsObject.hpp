#pragma once
#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <vector>


/**
 * This will be the wrapper class for physics
 * 
*/
namespace Physics
{
    class PhysicsObject {
        private:
            btCollisionShape* shape;
            btRigidBody* body;
            int tag;
        public:
            PhysicsObject();
            void createShape(std::vector<glm::vec3>, unsigned int, bool);
            void createBodyWithMass(float);
    };
} // namespace Game