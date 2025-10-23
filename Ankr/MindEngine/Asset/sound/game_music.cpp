//
// Created by muham on 14.10.2025.
//

#include "game_music.hpp"

#include <ranges>
#include <stdexcept>

AudioManager::AudioManager() {
    init();
}

AudioManager::~AudioManager() {
    Shutdown();
}

void AudioManager::init() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void AudioManager::playSound(const std::string& key, const std::string& path, const int loops) {
    if (Mix_Chunk* sound = loadSound(key, path); Mix_PlayChannel(-1, sound, loops) == -1) {
        throw std::runtime_error("Failed to play sound: " + std::string(Mix_GetError()));
    }
}

void AudioManager::playMusic(const std::string &key, const std::string& path, const int loops) {
    if (Mix_Music* music = loadMusic(key, path); Mix_PlayMusic(music, loops) == -1) {
        throw std::runtime_error("Failed to play music: " + std::string(Mix_GetError()));
    }
}

Mix_Chunk *AudioManager::loadSound(const std::string &key, const std::string &path) {
    if (const auto it = sounds.find(key); it != sounds.end()) {
        return it->second;
    }
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (!sound) {
        throw std::runtime_error("Failed to load sound: " + path + " Error: " + Mix_GetError());
    }
    sounds[key] = sound;
    return sound;
}

Mix_Music* AudioManager::loadMusic(const std::string &key, const std::string &path) {
    if (const auto it = musics.find(key); it != musics.end()) {
        return it->second;
    }
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        throw std::runtime_error("Failed to load music: " + path + " Error: " + Mix_GetError());
    }
    musics[key] = music;
    return music;
}

void AudioManager::Shutdown() {
    for (const auto &val: sounds | std::views::values) Mix_FreeChunk(val);

    for (const auto &val: musics | std::views::values) Mix_FreeMusic(val);

    sounds.clear();
    musics.clear();

    Mix_CloseAudio();
}