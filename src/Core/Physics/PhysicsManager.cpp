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
    float widthValue = ((this->windowWidth / 2.0f) / this->windowWidth  - 0.5f) * 2.0f;
    float heightValue = ((this->windowHeight / 2) / this->windowHeight - 0.5f) * -2.0f;

    glm::vec4 rayStart(
        widthValue,
        heightValue,
        -1.0,
        1.0f
    ); //= this->camera->getPickRay(windowInfo.width, windowInfo.height);
    glm::vec4 rayEnd(
        widthValue,
        heightValue,
        0.0,
        1.0f
    ); //= this->camera->getPosition();
    glm::vec3 lookDir = camera->getLookDirection();

    glm::mat4 invertMat = glm::inverse(camera->getProjection() * camera->getModelView());
    glm::vec4 rayStartWorld = invertMat * rayStart;
    rayStartWorld /= rayStartWorld.w;
    glm::vec4 rayEndWorld = invertMat * rayEnd;
    rayEndWorld /= rayEndWorld.w;

    glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
    rayDirWorld = glm::normalize(rayDirWorld);

    glm::vec3 origin(rayStartWorld);
    glm::vec3 direction(rayDirWorld);

    glm::vec3 end = origin + (direction * 5.0f);

    btVector3 btToRay = btVector3(end.x, end.y, end.z);
    btVector3 btFromRay = btVector3(origin.x, origin.y, origin.z);

    dynamicsWorld->updateAabbs();
    dynamicsWorld->computeOverlappingPairs();

    
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