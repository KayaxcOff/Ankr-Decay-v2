//
// Created by muham on 8.10.2025.
//

#ifndef ANKR_LIGHT_KINGDOM_HPP
#define ANKR_LIGHT_KINGDOM_HPP

#include <SDL2/SDL.h>
#include <string>
#include "../../Asset/image/game_images.hpp"

class AnkrBoard {
public:
    explicit AnkrBoard(ImageLoader* loader);
    ~AnkrBoard();

    void loadMapTex(const std::string &path);
    void drawBoard(SDL_Renderer* renderer) const;
private:
    SDL_Texture *texture;
    ImageLoader* imageLoader;
};

#endif //ANKR_LIGHT_KINGDOM_HPP