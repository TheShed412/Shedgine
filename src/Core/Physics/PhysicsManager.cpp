#include "PhysicsManager.hpp"

using namespace Physics;

PhysicsManager::PhysicsManager(int width, int height) {
    this->windowHeight = height;
    this->windowWidth = width;
    this->gravity = -15;
    this->debugMode = 0;
}

PhysicsManager::PhysicsManager(int debugMode, float gravity, int width, int height) {
    this->debugMode = debugMode;
    this->gravity = gravity;
    this->windowHeight = height;
    this->windowWidth = width;
}

/**
 * Executes the needed physics calculations at the end of frames that are called in the scenes
*/
void PhysicsManager::endFrameProcess(Rendering::Camera* camera, int elapsedTime) {
    dynamicsWorld->stepSimulation(btScalar(elapsedTime/1000.0f), 1, btScalar(1.0)/btScalar(60.0));
    this->castRays(camera);
    if (debugMode != 0) {
        debugDrawer->SetMatrices(camera->getModelView(), camera->getProjection());
        dynamicsWorld->debugDrawWorld();
    }
}

void PhysicsManager::setupCollisions() {
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    if (this->debugMode != 0) {
        this->debugDrawer = new GLDebugDrawer();
        dynamicsWorld->setDebugDrawer(this->debugDrawer);
    }
}

void PhysicsManager::addPhysicsObject(std::string objectName, PhysicsObject* newObject) {
    physicsObjects[objectName] = newObject;
}

void PhysicsManager::setDebugMode(int debugMode) {
    this->debugMode = debugMode;
}

void PhysicsManager::setGravity(float gravity) {
    this->gravity = gravity;
}

/**
 * This will do ray casts from the missle of the screen out
 * 
 * This will probably need generalized more and need seperated out more tto
 * keep gamecode with game stuff
*/
void PhysicsManager::castRays(Rendering::Camera* camera) {
    glm::vec3 end;
    glm::vec3 origin;

    camera->getPickRays(5.0f, &origin, &end);

    btVector3 btToRay = btVector3(end.x, end.y, end.z);
    btVector3 btFromRay = btVector3(origin.x, origin.y, origin.z);

    dynamicsWorld->updateAabbs();
    dynamicsWorld->computeOverlappingPairs();

    btCollisionWorld::ClosestRayResultCallback closestResult(btFromRay, btToRay);
    dynamicsWorld->rayTest(btFromRay, btToRay, closestResult);

    
    // if the left button is pressed
    // if (tmpButton == 1 && tmpState == 1) {
    //     btCollisionWorld::ClosestRayResultCallback closestResult(btFromRay, btToRay);

    //     dynamicsWorld->rayTest(btFromRay, btToRay, closestResult);
    //     if (closestResult.hasHit()) {
    //         const btRigidBody* pickedBody = btRigidBody::upcast(closestResult.m_collisionObject);


    //         //check if the body isn't static or kinematic so that I know it can be moved
    //         if (pickedBody->getMass() != 0) {
    //             std::cout << "origin:   " << origin.x << " " << origin.y << " " << origin.z << std::endl;
    //             std::cout << "end:     " << end.x << " " << end.y << " " << end.z << std::endl;
    //             std::cout << std::endl;
    //             btVector3 pickPos = closestResult.m_hitPointWorld;
    //             btVector3 localPivot = pickedBody->getCenterOfMassTransform().inverse() * pickPos;
    //         }
    //     }
    // } else if (tmpButton == 1 && tmpState == 0) {  // if the left button is released

    // }
}