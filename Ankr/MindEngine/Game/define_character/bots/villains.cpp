//
// Created by muham on 11.10.2025.
//

#include "villains.hpp"

#include <iostream>
#include "../base/hero_base.hpp"

DarkKnight::DarkKnight(b2Body *body, const float width, const float height, SDL_Texture *texture, PhysicsManager* physics) : Champions(body, width, height, texture, physics) {
    name = "Dark Knight";
    health = 150;
    maxHealth = 150;
    attackPower = 25;
}

void DarkKnight::useAbility(heroes::Champions *target, const int whichOne) {
    switch (whichOne) {
        case 1: shadowSlash(target); break;
        case 2: darkShield(); break;
        default: break;
    }
}

void DarkKnight::shadowSlash(heroes::Champions *target) const {
    target->takeDamage(attackPower);
    std::cout << name << " used Shadow Slash on " << target->getName() << " for " << attackPower << " damage!" << std::endl;
}

void DarkKnight::darkShield() {
    health += 10;
    if (health > maxHealth) health = maxHealth;
    std::cout << name << " used Dark Shield and healed for 10 health!" << std::endl;
}

MotherWitch::MotherWitch(b2Body *body, const float width, const float height, SDL_Texture *texture, PhysicsManager* physics) : Champions(body, width, height, texture, physics) {
    name = "Mother Witch";
    health = 60;
    maxHealth = 60;
    attackPower = 20;
}

void MotherWitch::useAbility(heroes::Champions *target, const int whichOne) {
    if (whichOne == 1) {
        darknessCurse(target);
    } else {
        std::cout << name << " has no other abilities!" << std::endl;
    }
}

void MotherWitch::darknessCurse(heroes::Champions *target) const {
    target->takeDamage(attackPower);
    std::cout << name << " used Darkness Curse on " << target->getName() << " for " << attackPower << " damage!" << std::endl;
}
