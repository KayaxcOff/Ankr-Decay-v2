//
// Created by muham on 7.10.2025.
//

#include "input_manager.hpp"

InputManager::InputManager() : keyboardState(nullptr) {}

InputManager::~InputManager() {
    Shutdown();
}

bool InputManager::isPressed(const SDL_Scancode key) const {
    if (keyboardState) {
        return keyboardState[static_cast<int>(key)] != 0;
    }
    return currentKeyStates.contains(key) ? currentKeyStates.at(key) : false;
}

bool InputManager::isTriggered(const SDL_Scancode key) const {
    return triggeredKeyStates.contains(key) ? triggeredKeyStates.at(key) : false;
}

void InputManager::handleEvent(const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.repeat == 0) {
            currentKeyStates[event.key.keysym.scancode] = true;
        }
    } else if (event.type == SDL_KEYUP) {
        currentKeyStates[event.key.keysym.scancode] = false;
    }
}

void InputManager::update() {
    if (keyboardState) {
        for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
            currentKeyStates[static_cast<SDL_Scancode>(i)] = keyboardState[i] != 0;
        }
    }

    triggeredKeyStates.clear();

    for (const auto& [key, currentlyPressed] : currentKeyStates) {
        if (const bool wasPreviouslyPressed = previousKeyStates.contains(key) ? previousKeyStates.at(key) : false; currentlyPressed && !wasPreviouslyPressed) {
            triggeredKeyStates[key] = true;
        } else {
            triggeredKeyStates[key] = false;
        }
    }

    previousKeyStates = currentKeyStates;
}

void InputManager::Shutdown() {
    keyboardState = nullptr;
    currentKeyStates.clear();
    previousKeyStates.clear();
    triggeredKeyStates.clear();
}

/*
bool InputManager::isPressed(const SDL_Scancode key) const {
    return triggeredKeyStates.contains(key) ? triggeredKeyStates.at(key) : false;
}

bool InputManager::isTriggered(const SDL_Scancode key) const {
    const bool currentlyPressed = currentKeyStates.contains(key) ? currentKeyStates.at(key) : false;
    const bool previouslyPressed = previousKeyStates.contains(key) ? previousKeyStates.at(key) : false;

    return currentlyPressed && !previouslyPressed;
}

void InputManager::handleEvent(const SDL_Event &event) {

    if (event.type == SDL_KEYDOWN) {
        if (event.key.repeat == 0) {
            currentKeyStates[event.key.keysym.scancode] = true;
        }
    } else if (event.type == SDL_KEYUP) {
        currentKeyStates[event.key.keysym.scancode] = false;
    }

}

void InputManager::update() {
    triggeredKeyStates.clear();

    for (const auto&[fst, snd] : currentKeyStates) {
        SDL_Scancode key = fst;
        const bool isCurrentlyPressed = snd;

        if (const bool wasPreviouslyPressed = previousKeyStates.contains(key) ? previousKeyStates.at(key) : false; isCurrentlyPressed && !wasPreviouslyPressed) {
            triggeredKeyStates[key] = true;
        } else {
            triggeredKeyStates[key] = false;
        }
    }

    previousKeyStates = currentKeyStates;
}

void InputManager::Shutdown() {
    keyboardState = nullptr;
    currentKeyStates.clear();
    previousKeyStates.clear();
    triggeredKeyStates.clear();
}
*/