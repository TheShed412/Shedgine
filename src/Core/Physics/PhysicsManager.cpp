#include "PhysicsManager.hpp"

using namespace Physics;

void collisionCheck(btDynamicsWorld *dynamicsWorld, btScalar timeStep) {
    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
}

PhysicsManager::PhysicsManager(int width, int height) {
    this->windowHeight = height;
    this->windowWidth = width;
    this->gravity = -15;
    this->debugMode = 0;
    this->setupCollisions();
}

PhysicsManager::PhysicsManager(int debugMode, float gravity, int width, int height) {
    this->debugMode = debugMode;
    this->gravity = gravity;
    this->windowHeight = height;
    this->windowWidth = width;
    this->setupCollisions();
}

/**
 * Executes the needed physics calculations at the end of frames that are called in the scenes
*/
void PhysicsManager::endFrameProcess(Rendering::Camera* camera, int elapsedTime) {
    for (auto physicsObject : physicsObjects){
        physicsObject.second->updateObjectPosition();
    }
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

    dynamicsWorld->setGravity(btVector3(0,this->gravity,0));
    dynamicsWorld->setInternalTickCallback(collisionCheck);
}

void PhysicsManager::addPhysicsObject(std::string objectName, PhysicsObject* newObject) {
    physicsObjects[objectName] = newObject;
    dynamicsWorld->addRigidBody(newObject->getRigidBody());
    
    collisionShapes.push_back(newObject->getCollisionShape());
}

void PhysicsManager::setDebugMode(int debugMode) {
    this->debugMode = debugMode;
}

void PhysicsManager::setGravity(float gravity) {
    this->gravity = gravity;
}

void PhysicsManager::setMouseState(int button, bool state) {
    this->mouseButton = button;
    this->mouseButtonPressed = state;
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
    if (closestResult.hasHit()) {
        const btRigidBody* pickedBody = btRigidBody::upcast(closestResult.m_collisionObject);
        if (this->mouseButton == 1 && this->mouseButtonPressed) {
            //check if the body isn't static or kinematic so that I know it can be moved
            if (pickedBody->getMass() != 0) {
                // Get the pointer to the ID of the object so I can pull it from the 
                std::string* shapeID = (std::string*)pickedBody->getUserPointer();
                Physics::PhysicsObject* pickedObject = physicsObjects[*shapeID];

                // Activate the object so physics stuff happens
                pickedObject->getRigidBody()->activate();
                // Set the object to the end location of the pick
                pickedObject->setPosition(end);
                // Turn gravity off so that it won't build up velocity while being held
                pickedObject->getRigidBody()->setGravity(btVector3(0.0f, 0.0f, 0.0f));
            }
        } else if (this->mouseButton == 1 && !this->mouseButtonPressed) {  // if the left button is released
            std::string* shapeID = (std::string*)pickedBody->getUserPointer();
            Physics::PhysicsObject* pickedObject = physicsObjects[*shapeID];

            // Activate so physics things can happen
            pickedObject->getRigidBody()->activate();
            // TODO: Move this logic to the physics object so that I can use other logic to turn gravity on
            // Turn gravity back on
            pickedObject->getRigidBody()->setGravity(btVector3(0.0f, -15.0f, 0.0f));
        }
    }
}