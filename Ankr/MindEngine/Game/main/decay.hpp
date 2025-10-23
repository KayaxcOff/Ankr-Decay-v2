//
// Created by muham on 7.10.2025.
//

#ifndef ANKR_DECAY_HPP
#define ANKR_DECAY_HPP

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>
#include "../define_character/base/hero_base.hpp"
#include "../define_character/base/villain_base.hpp"
#include "../board/game_map.hpp"
#include "../../Core/debug/ankr_debug.hpp"
#include "../../Core/physics_rules/physics_manager.hpp"
#include "../../Core/player_inputs/input_manager.hpp"
// #include "../../Core/graphics/animation/animation_system.hpp"
#include "../../Asset/image/game_images.hpp"
#include "../../Asset/sound/game_music.hpp"

class AnkrDecay {
public:
    AnkrDecay();

    ~AnkrDecay();

    void init(const std::string &title, int width, int height);
    void run();
    void shutdown();
    [[nodiscard]] bool isRunning() const;
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    int SCREEN_WIDTH, SCREEN_HEIGHT;
    bool isValid;
    const float ppm;

    struct vec2D {
        float posX;
        float posY;
    };

    struct entity_d {
        b2Body *body;
        SDL_Texture *texture;
    };

    template<typename T>
    struct entity_t {
        T *ptr;
        b2Body *body;
        vec2D velocity;
        int aIndex;
    };

    std::unique_ptr<PhysicsManager> physics_manager_;
    std::unique_ptr<ImageLoader> image_loader_;
    std::unique_ptr<AudioManager> audio_manager_;
    std::unique_ptr<InputManager> input_manager_;
    std::unique_ptr<AnkrBoard> ankr_board_;
    std::unique_ptr<AnkrDebug> ankr_debug_;

    /* === Animation System Placeholder ===
    std::unique_ptr<AnimationSprite> animation_sprite_ = std::make_unique<AnimationSprite>(); // animation
    std::unique_ptr<AnimationSystem> animation_system_ = std::make_unique<AnimationSystem>(); // animation
    AnimationClip animation_clip_; // animation
    */
    std::vector<std::unique_ptr<heroes::Champions> > heroes_;
    std::vector<std::unique_ptr<villains::Champions> > villains_;

    void Render() const;
    void InitObject();
    void CleanObject();
    void GameOver();
    void Update(float deltaTime);
    static void Move(b2Body *body, float velX, float velY);
};

#endif //ANKR_DECAY_HPP