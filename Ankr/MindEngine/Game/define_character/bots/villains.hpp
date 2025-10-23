//
// Created by muham on 11.10.2025.
//

#ifndef ANKR_VILLAINS_HPP
#define ANKR_VILLAINS_HPP

#include "../base/villain_base.hpp"

class DarkKnight final : public villains::Champions {
public:
    DarkKnight(b2Body* body, float width, float height, SDL_Texture* texture, PhysicsManager* physics);

    void useAbility(heroes::Champions *target, int whichOne) override;
private:
    void shadowSlash(heroes::Champions* target) const;
    void darkShield();
};

class MotherWitch final : public villains::Champions {
public:
    MotherWitch(b2Body* body, float width, float height, SDL_Texture* texture, PhysicsManager* physics);

    void useAbility(heroes::Champions *target, int whichOne) override;
private:
    void darknessCurse(heroes::Champions* target) const;
};

#endif //ANKR_VILLAINS_HPP