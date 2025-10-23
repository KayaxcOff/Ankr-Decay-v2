//
// Created by muham on 11.10.2025.
//

#ifndef ANKR_HEROES_HPP
#define ANKR_HEROES_HPP

#include "../base/hero_base.hpp"

using namespace heroes;

class Aether final : public Champions {
public:
    Aether(b2Body* body, float width, float height, SDL_Texture* texture, PhysicsManager* physics);

    std::string displayInfo() override;

    void useAbility(villains::Champions *target, int whichOne) override;
private:
    void cosmicStrike(villains::Champions* target) const;
    void heavenlyShield();
    void divineTeleport(float newX, float newY);
};

class Synax final : public Champions {
public:
    Synax(b2Body* body, float width, float height, SDL_Texture* texture, PhysicsManager* physics);

    std::string displayInfo() override;

    void useAbility(villains::Champions *target, int whichOne) override;
private:
    void deathEyes(villains::Champions* target) const;
    void closeToDeath(villains::Champions* target) const;
    void deadlyHeal();
};

class Kahray final : public Champions {
public:
    Kahray(b2Body* body, float width, float height, SDL_Texture* texture, PhysicsManager* physics);

    std::string displayInfo() override;

    void useAbility(villains::Champions *target, int whichOne) override;
private:
    void hummerCrash(villains::Champions* target) const;
    void shield();
};

#endif //ANKR_HEROES_HPP