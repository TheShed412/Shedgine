#pragma once
#include <btBulletDynamicsCommon.h>


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
    };
} // namespace Game