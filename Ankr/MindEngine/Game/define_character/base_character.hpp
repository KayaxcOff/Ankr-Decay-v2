//
// Created by muham on 7.10.2025.
//

#ifndef ANKR_MAIN_CHARACTER_CLASS_HPP
#define ANKR_MAIN_CHARACTER_CLASS_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "../../Core/graphics/object/object_system.hpp"
#include "../../Core/physics_rules/physics_manager.hpp"

class BaseCharacter : public Object2D {
protected:
    std::string name;
    int health;
    int maxHealth;
    int attackPower;

    PhysicsManager* manager_;
public:
    BaseCharacter(b2Body* body, const float width, const float height, SDL_Texture* texture, PhysicsManager* manager) : Object2D(body, width, height, texture), name("Base Object"), health(0), maxHealth(0), attackPower(0), manager_(manager) {}
    ~BaseCharacter() override = default;

    void takeDamage(const int damage) {
        health -= damage;
        std::cout << name << " took " << damage << " damage. Current health: " << health << std::endl;
    }

    struct pos2D {
        float playX;
        float playY;
    };

    pos2D velocity{};

    void setBody(b2Body* _body) {
        body = _body;
    }

    void setPosition(const float x, const float y) {
        velocity.playX = x;
        velocity.playY = y;

        width = velocity.playX;
        height = velocity.playY;
    }

    void setTexture(SDL_Texture* _texture) {
        if (texture && texture != _texture) {
            SDL_DestroyTexture(texture);
        }

        texture = _texture;
    }

    [[nodiscard]] b2Body* getBody() const override {return body;}
    [[nodiscard]] float getWidth() const override {return width;}
    [[nodiscard]] float getHeight() const override {return height;}
    [[nodiscard]] SDL_Texture* getTexture() const override {return texture;}

    [[nodiscard]] pos2D getPosition() const {return velocity;}
    [[nodiscard]] bool isAlive() const {return health > 0;}
    [[nodiscard]] int getHealth() const {return health;}
    [[nodiscard]] std::string getName() const {return name;}
};

#endif //ANKR_MAIN_CHARACTER_CLASS_HPP