//
// Created by muham on 8.10.2025.
//

#include "game_images.hpp"

#include <iostream>
#include <ranges>
#include <SDL2/SDL_image.h>

ImageLoader::ImageLoader(SDL_Renderer* render) : renderer(render) {
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);

    if (constexpr int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF; !(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize!" << std::endl;
        std::cerr << IMG_GetError() << std::endl;
    }
}

ImageLoader::~ImageLoader() {
    Shutdown();
}

void ImageLoader::cleanTextures(SDL_Texture* texture) {
    if (const auto it = std::ranges::find_if(textures, [texture](const auto& pair) { return pair.second == texture; }); it != textures.end()) {
        SDL_DestroyTexture(it->second);
        textures.erase(it);
    }
}

void ImageLoader::Shutdown() {
    for (const auto &val: textures | std::views::values) {
        SDL_DestroyTexture(val);
    }
    textures.clear();
    IMG_Quit();
}

SDL_Texture *ImageLoader::loadTexture(const std::string &path) {
    if (!renderer) {
        std::cout << "Renderer is null" << std::endl;
        std::cerr << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());

    if (!texture) {
        std::cerr << "Error: Renderer is null when trying to load texture: " << path << std::endl;
        std::cerr << IMG_GetError() << std::endl;
        return nullptr;
    }

    textures[path] = texture;
    return texture;
}
