#include "PhysicsObject.hpp"

using namespace Physics;

std::vector<glm::vec3> getVertsFromVertexFormat(std::vector<Rendering::VertexFormat> vertexFormats) {
    std::vector<glm::vec3> verts;

    for (size_t i = 0; i < vertexFormats.size(); i++)
    {
        verts.push_back(vertexFormats.at(i).position); 
    }
    
    return verts;
}

PhysicsObject::PhysicsObject(unsigned int tag, float mass, bool isConvex, std::string filename)
: LoadedObject(filename)
{
    this->rotationX = 0;
    this->rotationY = 0;
    this->rotationZ = 0;

    this->isConvex = isConvex;
    this->mass = mass;
}

void PhysicsObject::Create() {
    LoadedObject::Create();

    this->createShape(getVertsFromVertexFormat(this->getVerts()), tag, isConvex);
    this->createBodyWithMass(mass);
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

        // TODO: more elegantly handle no verts
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
    btQuaternion rotation;
    rotation.setEulerZYX(rotationZ, rotationY, rotationX);

    btVector3 position = btVector3(this->currentLocation.x, this->currentLocation.y, this->currentLocation.z);

    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(rotation, position));

    btScalar bodyMass = mass;
    btVector3 bodyInertia;
    shape->calculateLocalInertia(bodyMass, bodyInertia);

    btRigidBody::btRigidBodyConstructionInfo bodyInfo = btRigidBody::btRigidBodyConstructionInfo(bodyMass, 
                                                                motionState, shape, bodyInertia);

    // TODO: these should be values passed in
    bodyInfo.m_restitution = 0.9f;
    bodyInfo.m_friction = 0.5f;

    body = new btRigidBody(bodyInfo);
    body->setUserPointer((void*) this);
    body->setLinearFactor(btVector3(1,1,0));
}

btRigidBody* PhysicsObject::getRigidBody() {
    return this->body;
}

btCollisionShape* PhysicsObject::getCollisionShape() {
    return this->shape;
}

void PhysicsObject::setPosition(glm::vec3 pos) {
    LoadedObject::setPosition(pos);
    btTransform trans = body->getWorldTransform();
    trans.setOrigin(btVector3(pos.x, pos.y, pos.z));
    body->setWorldTransform(trans);
} 

glm::vec3 PhysicsObject::getPosition() {
    btTransform trans = body->getWorldTransform();
    return glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
}

void PhysicsObject::updateObjectPosition() {
    btTransform trans = body->getWorldTransform();
    glm::vec3 newPos = glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
    setPosition(newPos);
}