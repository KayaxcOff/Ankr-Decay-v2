//
// Created by muham on 11.10.2025.
//

#include "object_system.hpp"

Object2D::Object2D(b2Body* body, const float width, const float height, SDL_Texture*texture) : body(body), width(width), height(height), texture(texture) {}

Object2D::~Object2D() {
    Object2D::Shutdown();
}

void Object2D::render(SDL_Renderer *renderer, const float ppm, int screenWidth, const int screenHeight) const {
    if (!renderer || !body || !texture) return;

    const b2Vec2 pos = body->GetPosition();

    const SDL_Rect dst {
        static_cast<int>(pos.x * ppm - (width * ppm) / 2),
        static_cast<int>(static_cast<float>(screenHeight) - (pos.y * ppm) - (height * ppm) / 2),
        static_cast<int>(width * ppm),
        static_cast<int>(height * ppm)
    };

    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void Object2D::Shutdown() {
    if (body) {
        if (b2World* world = body->GetWorld()) {
            world->DestroyBody(body);
        }
        body = nullptr;
    }
}

b2Body* Object2D::getBody() const {
    return body;
}

float Object2D::getWidth() const {
    return width;
}

float Object2D::getHeight() const {
    return height;
}

SDL_Texture* Object2D::getTexture() const {
    return texture;
}