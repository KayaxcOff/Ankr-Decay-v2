//
// Created by muham on 11.10.2025.
//

#ifndef ANKR_ENTITY_HPP
#define ANKR_ENTITY_HPP

#include <SDL2/SDL.h>
#include <Box2D/box2d.h>

class Object2D {
protected:
    b2Body* body;
    float width;
    float height;
    SDL_Texture* texture;
public:
    Object2D(b2Body* body, float width, float height, SDL_Texture* texture);

    virtual ~Object2D();

    void render(SDL_Renderer* renderer, float ppm, int screenWidth, int screenHeight) const;

    virtual void Shutdown();

    [[nodiscard]] virtual b2Body* getBody() const;
    [[nodiscard]] virtual float getWidth() const;
    [[nodiscard]] virtual float getHeight() const;
    [[nodiscard]] virtual SDL_Texture* getTexture() const;
};

#endif //ANKR_ENTITY_HPP