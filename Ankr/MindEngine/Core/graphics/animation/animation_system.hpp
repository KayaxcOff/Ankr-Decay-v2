//
// Created by muham on 12.10.2025.
//

#ifndef ANKR_ANIMATION_SYSTEM_HPP
#define ANKR_ANIMATION_SYSTEM_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <unordered_set>

struct AnimationClip {
    SDL_Texture* texture;
    std::vector<SDL_Rect> frames;
    float FPS = 12.0f;
};

class AnimationSprite {
public:
    AnimationSprite();

    void setClip(AnimationClip* clip);
    void play();
    void stop();
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, int x, int y) const;
private:
    bool isPlaying;
    float time;
    int frameIdx;
    AnimationClip* animation_clip_;
};

class AnimationSystem {
public:
    void Add(AnimationSprite* sprite);
    void Remove(AnimationSprite* sprite);
    void Update(float deltaTime) const;
private:
    std::unordered_set<AnimationSprite*> animation_sprites_;
};

#endif //ANKR_ANIMATION_SYSTEM_HPP