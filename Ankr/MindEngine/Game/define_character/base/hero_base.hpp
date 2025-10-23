//
// Created by muham on 11.10.2025.
//

#ifndef ANKR_HERO_BASE_HPP
#define ANKR_HERO_BASE_HPP

#include "../base_character.hpp"

namespace villains {
    class Champions;
}

namespace heroes {
    class Champions : public BaseCharacter {
    public:
        Champions(b2Body* body, const float width, const float height, SDL_Texture* texture, PhysicsManager* physics) : BaseCharacter(body, width, height, texture, physics) {}
        ~Champions() override = default;

        virtual std::string displayInfo() = 0;
        virtual void useAbility(villains::Champions* target, int whichOne) = 0;

        [[nodiscard]] bool isUsingAbility() const {return usingAbility;}
        void setUsingAbility(const bool value) {usingAbility = value;}
    private:
        bool usingAbility = false;
    };
}

#endif //ANKR_HERO_BASE_HPP