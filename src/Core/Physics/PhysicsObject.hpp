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
            bool isConvex;
            float mass;
            float restitution;
            float friction;
            float rotationZ;
            float rotationY;
            float rotationX;
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
            // TODO: Make these take vec3s for rotation
            void setRotationX(float);
            void setRotationY(float);
            void setRotationZ(float);
            float getRotationX();
            float getRotationY();
            float getRotationZ();
    };
} // namespace Game