#include "PhysicsObject.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"

using namespace Physics;

std::vector<glm::vec3> getVertsFromVertexFormat(std::vector<Rendering::VertexFormat> vertexFormats) {
    std::vector<glm::vec3> verts;

    for (size_t i = 0; i < vertexFormats.size(); i++)
    {
        verts.push_back(vertexFormats.at(i).position); 
    }
    
    return verts;
}

PhysicsObject::PhysicsObject(unsigned int tag, float mass, bool isConvex, float restitution, float friction, std::string filename)
: LoadedObject(filename)
{
    this->physicsRotation = glm::vec3(0.0);

    this->isConvex = isConvex;
    this->mass = mass;

    this->restitution = restitution;
    this->friction = friction;
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
    rotation.setEulerZYX(physicsRotation.z, physicsRotation.y, physicsRotation.x);

    btVector3 position = btVector3(this->currentLocation.x, this->currentLocation.y, this->currentLocation.z);

    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(rotation, position));

    btScalar bodyMass = mass;
    btVector3 bodyInertia;
    shape->calculateLocalInertia(bodyMass, bodyInertia);

    btRigidBody::btRigidBodyConstructionInfo bodyInfo = btRigidBody::btRigidBodyConstructionInfo(bodyMass, 
                                                                motionState, shape, bodyInertia);

    // TODO: these should be values passed in
    bodyInfo.m_restitution = this->restitution;
    bodyInfo.m_friction = this->friction;

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

    btMatrix3x3 rotMatrix = btMatrix3x3(body->getWorldTransform().getRotation());
    float x,y,z;
    //btQuaternion
    // Values are returned from -180 to 180
    rotMatrix.getEulerZYX(z, y, x);

    setRotation(glm::vec3(x, y, z));
}

const btScalar RADIANS_PER_DEGREE = M_PI / btScalar(180.0);
void PhysicsObject::setAngle(float angle, btVector3 rotVec) {

    btTransform trans = body->getWorldTransform();
    btQuaternion rot = trans.getRotation();
    btQuaternion diffRot = btQuaternion(rotVec, angle * RADIANS_PER_DEGREE);
    rot = diffRot * rot;

    trans.setRotation(rot);
    body->setWorldTransform(trans);
}

float getDiff(float prevX, float currX, std::string let) {
    float xAngleDiff = prevX - currX;

    // // Spinning from +180 to -180
    // if (prevX > glm::radians(175.0) && currX < 0) {
    //     float prevDiff = M_PI - abs(prevX);
    //     float currDiff = M_PI - abs(currX);
    //     xAngleDiff = prevDiff + currDiff;
    // }
    // // Spinning from -180 to +180
    // if (currX > glm::radians(175.0) && prevX < 0) {
    //     float prevDiff = M_PI - abs(prevX);
    //     float currDiff = M_PI - abs(currX);
    //     xAngleDiff = -1 * (prevDiff + currDiff);
    // }
    // // going from -1 to +1
    // if (prevX < glm::radians(20.0) && prevX > 0 && currX < 0) {
    //     float prevDiff = 0 + abs(prevX);
    //     float currDiff = 0 + abs(currX);
    //     xAngleDiff = -1 * (prevDiff + currDiff);
    // }
    // // going from +1 to -1
    // if (currX < glm::radians(20.0) && currX > 0 && prevX < 0) {
    //     float prevDiff = 0 + abs(prevX);
    //     float currDiff = 0 + abs(currX);
    //     xAngleDiff = (prevDiff + currDiff);
    // }


    return xAngleDiff;
}


void PhysicsObject::setRotation(glm::vec3 rotation) {

    float prevX = physicsRotation.x;
    float currX = rotation.x;

    float prevY = physicsRotation.y;
    float currY = rotation.y;

    float prevZ = physicsRotation.z;
    float currZ = rotation.z;

    float xAngleDiff = getDiff(prevX, currX, "X");
    //this->setAngle(currX, btVector3(1, 0, 0));

    float yAngleDiff = getDiff(prevY, currY, "Y");
    //this->setAngle(currY, btVector3(0, 1, 0));

    float zAngleDiff = getDiff(prevZ, currZ, "Z");
    //this->setAngle(currZ, btVector3(0, 0, 1));

    // std::cout << " prev x:\t\t" << glm::degrees(physicsRotation.x) << std::endl;
    this->physicsRotation = rotation;


    // float newX = rotation.x;
    totalXDiff += xAngleDiff;

    // float newY = rotation.y;
    totalYDiff += yAngleDiff;

    float newZ = rotation.z;
    totalZDiff += zAngleDiff;
    // std::cout << " new x:\t\t\t" << glm::degrees(rotation.x) << std::endl;
    // std::cout << " new diff x:\t\t" << glm::degrees(xAngleDiff) << std::endl;
    // std::cout << " x:\t\t\t" << glm::degrees(totalXDiff) << std::endl;

    // This sets the position of an object to the given value
    // it is up to the caller to do the accumulation
    LoadedObject::setRotation(glm::vec3(totalXDiff, totalYDiff, totalZDiff));
}

glm::vec3 PhysicsObject::getRotation() {
    btMatrix3x3 rotMatrix = btMatrix3x3(body->getWorldTransform().getRotation());
    float x,y,z;
    rotMatrix.getEulerZYX(z, y, x);
    return glm::vec3(glm::degrees(x), glm::degrees(y), glm::degrees(z));
}

