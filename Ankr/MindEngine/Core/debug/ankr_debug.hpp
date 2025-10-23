//
// Created by muham on 19.10.2025.
//

#ifndef ANKR_ANKR_DEBUG_HPP
#define ANKR_ANKR_DEBUG_HPP

#include <SDL2/SDL.h>
#include "../../Game/define_character/base/hero_base.hpp"

class AnkrDebug {
public:
    explicit AnkrDebug(SDL_Renderer* renderer);
    ~AnkrDebug();

    void init(SDL_Window* window);
    void setHero(const heroes::Champions* champion);
    void setVillain(const villains::Champions* champion);
    void handleEvent(const SDL_Event& event) const;
    void newFrame() const;
    void render() const;
    void shutdown() const;
    void displayGUI();
    void setInformation();
    //void setIndex() const;
    //[[nodiscard]] int getIndex() const;
private:

    mutable bool initialized;
    mutable int abilityIndex;
    const heroes::Champions* hero;
    const villains::Champions* villain;

    SDL_Renderer* renderer;

    bool shouldWarning;
};

#endif //ANKR_ANKR_DEBUG_HPP