//
// Created by muham on 7.10.2025.
//

#ifndef ANKR_INPUTS_HPP
#define ANKR_INPUTS_HPP

#include <SDL2/SDL.h>
#include <unordered_map>

class InputManager {
public:
    InputManager();
    ~InputManager();

    [[nodiscard]] bool isPressed(SDL_Scancode key) const;
    [[nodiscard]] bool isTriggered(SDL_Scancode key) const;

    void handleEvent(const SDL_Event &event);
    void update();
    void Shutdown();
private:
    const Uint8* keyboardState;
    std::unordered_map<SDL_Scancode, bool> currentKeyStates;
    std::unordered_map<SDL_Scancode, bool> previousKeyStates;
    std::unordered_map<SDL_Scancode, bool> triggeredKeyStates;
};

#endif //ANKR_INPUTS_HPP