//
// Created by muham on 14.10.2025.
//

#ifndef ANKR_MUSICS_HPP
#define ANKR_MUSICS_HPP

#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <string>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void init();
    void playSound(const std::string& key, const std::string& path, int loops=0);
    void playMusic(const std::string& key, const std::string& path, int loops=0);
    void Shutdown();
private:
    Mix_Chunk* loadSound(const std::string& key,const std::string& path);
    Mix_Music* loadMusic(const std::string& key,const std::string& path);

    std::unordered_map<std::string, Mix_Chunk*> sounds;
    std::unordered_map<std::string, Mix_Music*> musics;
};

#endif //ANKR_MUSICS_HPP