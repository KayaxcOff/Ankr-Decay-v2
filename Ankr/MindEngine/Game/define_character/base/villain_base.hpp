//
// Created by muham on 11.10.2025.
//

#ifndef ANKR_VILLAIN_BASE_HPP
#define ANKR_VILLAIN_BASE_HPP

#include "../base_character.hpp"

namespace heroes {
    class Champions;
}

namespace villains {
    class Champions : public BaseCharacter {
    public:
        Champions(b2Body* body, const float width, const float height, SDL_Texture* texture, PhysicsManager* physics) : BaseCharacter(body, width, height, texture, physics) {}
        ~Champions() override = default;

        virtual void useAbility(heroes::Champions* target, int whichOne) = 0;

        [[nodiscard]] bool isUsingAbility() const {return usingAbility;}
        void setUsingAbility(const bool value) {usingAbility = value;}
    private:
        bool usingAbility = false;
    };
}

#endif //ANKR_VILLAIN_BASE_HPP