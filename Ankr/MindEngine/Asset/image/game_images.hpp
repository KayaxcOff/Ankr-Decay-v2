//
// Created by muham on 7.10.2025.
//

#ifndef ANKR_GAME_IMAGES_HPP
#define ANKR_GAME_IMAGES_HPP

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

class ImageLoader {
public:
    explicit ImageLoader(SDL_Renderer* render);
    ~ImageLoader();

    void cleanTextures(SDL_Texture* texture);
    void Shutdown();
    SDL_Texture* loadTexture(const std::string& path);
private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> textures;
};

#endif //ANKR_GAME_IMAGES_HPP