#pragma once
#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <vector>

#include "../../Rendering/Models/LoadedObject.hpp"
#include "../../Rendering/VertexFormat.hpp"


/**
 * This will be the wrapper class for physics
 * 
*/
namespace Physics
{
    class PhysicsObject : public Rendering::Models::LoadedObject {
        private:
            btCollisionShape* shape;
            btRigidBody* body;
            // TODO: make an enum for tags so behavior can be defined
            int tag;
            bool isStatic; // immovable
            bool isKinematic; // movable only with code
            bool isConvex;
            float mass;
            float restitution;
            float friction;
            // The temp accumulator for x
            float totalXDiff = 0.0;
            float totalYDiff = 0.0;
            float totalZDiff = 0.0;
            glm::vec3 physicsRotation;
            void setAngle(float, btVector3);
        public:
            PhysicsObject(unsigned int,float,bool,float,float,std::string);
            void createShape(std::vector<glm::vec3>, unsigned int, bool);
            void createBodyWithMass(float);
            void Create();
            btRigidBody* getRigidBody();
            btCollisionShape* getCollisionShape();
            void setPosition(glm::vec3);
            glm::vec3 getPosition();
            void updateObjectPosition();
    };
} // namespace Game