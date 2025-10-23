//
// Created by muham on 11.10.2025.
//

#include "heroes.hpp"

#include <iostream>
#include "../base/villain_base.hpp"

Aether::Aether(b2Body *body, const float width, const float height, SDL_Texture *texture, PhysicsManager* physics) : Champions(body, width, height, texture, physics) {
    name = "Aether";
    health = 75;
    maxHealth = 110;
    attackPower = 30;
}

std::string Aether::displayInfo() {
    std::string info = "Name: " + name + "\n" + "Health: " + std::to_string(health) + "/" + std::to_string(maxHealth) + "\n" + "Attack Power: " + std::to_string(attackPower) + "\n";
    return info;
}

void Aether::useAbility(villains::Champions *target, const int whichOne) {
    std::cout << name << " is using " << whichOne << ". ability" <<std::endl;

    switch (whichOne) {
        case 1: cosmicStrike(target); break;
        case 2: heavenlyShield(); break;
        case 3: divineTeleport(0, 0); break;
        default: std::cout << "Invalid choice" << std::endl; break;
    }
}

void Aether::cosmicStrike(villains::Champions *target) const {
    target->takeDamage(attackPower);
    std::cout << name << " used Cosmic Strike on " << target->getName() << " for " << attackPower << " damage!" << std::endl;
}

void Aether::heavenlyShield() {
    std::cout << name << " used Heavenly Shield and increased defense!" << std::endl;
    health = maxHealth;
}

void Aether::divineTeleport(float newX, float newY) {
    setPosition(newX, newY);
    std::cout << name << " used Divine Teleport to (" << newX << ", " << newY << ")!" << std::endl;
}

Synax::Synax(b2Body *body, const float width, const float height, SDL_Texture *texture, PhysicsManager* physics) : Champions(body, width, height, texture, physics) {
    name = "Synax";
    health = 90;
    maxHealth = 90;
    attackPower = 25;
}

std::string Synax::displayInfo() {
    std::string info = "Name: " + name + "\n" + "Health: " + std::to_string(health) + "/" + std::to_string(maxHealth) + "\n" + "Attack Power: " + std::to_string(attackPower) + "\n";
    return info;
}

void Synax::useAbility(villains::Champions *target, const int whichOne) {
    std::cout << name << " is using " << whichOne << ". ability" << std::endl;

    switch (whichOne) {
        case 1: deathEyes(target); break;
        case 2: closeToDeath(target); break;
        case 3: deadlyHeal(); break;
        default: std::cout << "Invalid choice" << std::endl; break;
    }
}

void Synax::deathEyes(villains::Champions *target) const {
    target->takeDamage(attackPower);
    std::cout << name << " used Death Eyes on " << target->getName() << " for " << attackPower << " damage!" << std::endl;
}

void Synax::closeToDeath(villains::Champions *target) const {
    const int damage = target->getHealth() - 25;
    target->takeDamage(damage);
    std::cout << name << " used Close to Death on " << target->getName() << ", reducing their health to 10!" << std::endl;
}

void Synax::deadlyHeal() {
    health += 10;
    if (health > maxHealth) health = maxHealth;
    std::cout << name << " used Deadly Heal and restored 10 health!" << std::endl;
}

Kahray::Kahray(b2Body *body, const float width, const float height, SDL_Texture *texture, PhysicsManager* physics) : Champions(body, width, height, texture, physics) {
    name = "Kahray";
    health = 30;
    maxHealth = 70;
    attackPower = 10;
}

std::string Kahray::displayInfo() {
    std::string info = "Name: " + name + "\n" + "Health: " + std::to_string(health) + "/" + std::to_string(maxHealth) + "\n" + "Attack Power: " + std::to_string(attackPower) + "\n";
    return info;
}

void Kahray::useAbility(villains::Champions *target, const int whichOne) {
    switch (whichOne) {
        case 1: hummerCrash(target); break;
        case 2: shield(); break;
        default: std::cout << "Invalid choice" << std::endl; break;
    }
}

void Kahray::hummerCrash(villains::Champions *target) const {
    target->takeDamage(attackPower);
    std::cout << name << " used Hummer Crash on " << target->getName() << " for " << attackPower << " damage!" << std::endl;
}

void Kahray::shield() {
    health += 5;
    if (health > maxHealth) health = maxHealth;
    std::cout << name << " used Shield and restored 5 health!" << std::endl;
}
