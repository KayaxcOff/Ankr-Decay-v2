//
// Created by muham on 8.10.2025.
//

#ifndef ANKR_PHYSICS_MANAGEMENT_HPP
#define ANKR_PHYSICS_MANAGEMENT_HPP

#include <Box2D/box2d.h>

class PhysicsManager {
public:
    PhysicsManager();
    ~PhysicsManager();

    void Init(float pixelsPerMeter, float gravityX, float gravityY);
    void Step(float deltaTime, int velocityIterations, int positionIterations) const;
    void calculateCollision(b2Body* body, float width, float height, int offsetX, int offsetY) const;
    void clean();
    void Shutdown();
    [[nodiscard]] b2Body* initializeBox(float px, float py, float width, float height, bool isDynamic) const;
private:
    float ppm;
    b2World* world;
};

#endif //ANKR_PHYSICS_MANAGEMENT_HPP