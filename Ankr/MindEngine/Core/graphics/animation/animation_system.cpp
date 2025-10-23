//
// Created by muham on 12.10.2025.
//

#include "animation_system.hpp"

AnimationSprite::AnimationSprite() : isPlaying(true), time(0.0f), frameIdx(0), animation_clip_(nullptr) {}

void AnimationSprite::setClip(AnimationClip *clip) {
    animation_clip_ = clip;
    frameIdx = 0;
    time = 0.0f;
}

void AnimationSprite::play() {
    isPlaying = true;
}

void AnimationSprite::stop() {
    isPlaying = false;
}

void AnimationSprite::update(const float deltaTime) {
    if (!isPlaying || !animation_clip_ || animation_clip_->frames.empty()) {
        return;
    }

    time += deltaTime;

    const float frameDuration = 1.0f / animation_clip_->FPS;

    while (time >= frameDuration) {
        time -= frameDuration;
        frameIdx = (frameIdx + 1) % animation_clip_->frames.size();
    }
}

void AnimationSprite::render(SDL_Renderer *renderer, const int x, const int y) const {
    if (!animation_clip_ || animation_clip_->frames.empty()) return;

    const SDL_Rect& srcRect = animation_clip_->frames[frameIdx];
    const SDL_Rect destRect = { x, y, srcRect.w, srcRect.h };

    SDL_RenderCopy(renderer, animation_clip_->texture, &srcRect, &destRect);
}

void AnimationSystem::Add(AnimationSprite *sprite) {
    animation_sprites_.insert(sprite);
}

void AnimationSystem::Remove(AnimationSprite *sprite) {
    animation_sprites_.erase(sprite);
}

void AnimationSystem::Update(const float deltaTime) const {
    for (auto* item : animation_sprites_) {
        item->update(deltaTime);
    }
}
