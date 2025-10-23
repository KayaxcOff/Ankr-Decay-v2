//
// Created by muham on 8.10.2025.
//

#include "physics_manager.hpp"

#include <iostream>

PhysicsManager::PhysicsManager() : ppm(100.0f), world(nullptr) {}
PhysicsManager::~PhysicsManager() {
    Shutdown();
}

void PhysicsManager::Init(const float pixelsPerMeter, const float gravityX, const float gravityY) {
    ppm = pixelsPerMeter;
    world = new b2World(b2Vec2(gravityX, gravityY));
}

void PhysicsManager::Step(const float deltaTime, const int velocityIterations, const int positionIterations) const {
    if (!world) return;
    world->Step(deltaTime, velocityIterations, positionIterations);
}

void PhysicsManager::calculateCollision(b2Body *body, const float width, const float height, const int offsetX, const int offsetY) const {
    b2Vec2 position = body->GetPosition();
    b2Vec2 velocity = body->GetLinearVelocity();

    const float halfX = width / 2.0f;
    const float halfY = height * 0.5f;

    const float screenWidth = static_cast<float>(offsetX) / ppm;
    const float screenHeight = static_cast<float>(offsetY) / ppm;

    bool isNeed = false;

    if (position.x - halfX < 0.0f) {
        position.x = halfX;
        velocity.x = 0.0f;
        isNeed = true;
    } else if (position.x + halfX > screenWidth) {
        position.x = screenWidth - halfX;
        velocity.x = 0.0f;
        isNeed = true;
    }

    if (position.y - halfY < 0.0f) {
        position.y = halfY;
        velocity.y = 0.0f;
        isNeed = true;
    } else if (position.y + halfY > screenHeight) {
        position.y = screenHeight - halfY;
        velocity.y = 0.0f;
        isNeed = true;
    }

    if (isNeed) {
        body->SetTransform(position, body->GetAngle());
        body->SetLinearVelocity(velocity);
    }
}

void PhysicsManager::clean() {
    if (world) {
        for (b2Body* body = world->GetBodyList(); body != nullptr; body = body->GetNext()) world->DestroyBody(body);
        delete world;
        world = nullptr;
        std::cout << "All physics objects cleaned up." << std::endl;
    }
}

void PhysicsManager::Shutdown() {
    if (world != nullptr) {
        delete world;
        world = nullptr;
    }
}

b2Body *PhysicsManager::initializeBox(const float px, const float py, const float width, const float height, const bool isDynamic) const {
    b2BodyDef bodyDef;
    bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
    bodyDef.position.Set(px , py);
    b2Body* body = world->CreateBody(&bodyDef);

    if (isDynamic) {
        bodyDef.linearDamping = 0.0f;
        bodyDef.angularDamping = 0.0f;
        bodyDef.allowSleep = false;
        bodyDef.fixedRotation = false;
    }

    b2PolygonShape boxShape;
    boxShape.SetAsBox(width / 2, height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = isDynamic ? 1.0f : 0.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
    return body;
}
