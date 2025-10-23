//
// Created by muham on 8.10.2025.
//

#include "game_map.hpp"

AnkrBoard::AnkrBoard(ImageLoader* loader) : texture(nullptr), imageLoader(loader) {}

AnkrBoard::~AnkrBoard() {
    imageLoader->cleanTextures(texture);
}

void AnkrBoard::loadMapTex(const std::string &path) {
    texture = imageLoader->loadTexture(path);
}

void AnkrBoard::drawBoard(SDL_Renderer *renderer) const {
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    }
}
