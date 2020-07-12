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
            int tag;
            bool isConvex;
            float mass;
            int rotationZ;
            int rotationY;
            int rotationX;
        public:
            PhysicsObject(unsigned int,float,bool,std::string);
            void createShape(std::vector<glm::vec3>, unsigned int, bool);
            void createBodyWithMass(float);
            void Create();
            btRigidBody* getRigidBody();
            void setPosition(glm::vec3);
            glm::vec3 getPosition();
    };
} // namespace Game