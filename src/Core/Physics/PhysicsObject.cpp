#include "PhysicsObject.hpp"

using namespace Physics;

PhysicsObject::PhysicsObject() {

}

void PhysicsObject::createShape(std::vector<glm::vec3> vertecies, unsigned int tag, bool isConvex) {
    if (isConvex) {
        shape = new btConvexHullShape();

        for(int i = 0; i < vertecies.size(); i++) {
            glm::vec3 vector = vertecies[i];
            btVector3 btv = btVector3(vector.x, vector.y, vector.z);
            ((btConvexHullShape*) shape)->addPoint(btv);
        }
    } else {
        btTriangleMesh* mesh = new btTriangleMesh();

        for(int i = 0; i < vertecies.size(); i+=3) {
            glm::vec3 vert1 = vertecies[i];
            glm::vec3 vert2 = vertecies[i+1];
            glm::vec3 vert3 = vertecies[i+2];

            btVector3 bv1 = btVector3(vert1.x, vert1.y, vert1.z);
            btVector3 bv2 = btVector3(vert2.x, vert2.y, vert2.z);
            btVector3 bv3 = btVector3(vert3.x, vert3.y, vert3.z);

            mesh->addTriangle(bv1, bv2, bv3);
        }
        shape = new btBvhTriangleMeshShape(mesh, true);
    }
    
}

void PhysicsObject::createBodyWithMass(float mass) {
    
}