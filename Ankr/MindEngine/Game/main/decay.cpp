//
// Created by muham on 7.10.2025.
//

#include "decay.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>
#include "imgui.h"
#include "../define_character/characters/heroes.hpp"
#include "../define_character/bots/villains.hpp"

constexpr int TARGET_FPS = 60;
constexpr int FRAME_DELAY = 1000 / TARGET_FPS;

AnkrDecay::AnkrDecay() : window(nullptr), renderer(nullptr), SCREEN_WIDTH(1200), SCREEN_HEIGHT(800), isValid(false), ppm(100.0f){
    init("Ankr:Decay-v2.0", SCREEN_WIDTH, SCREEN_HEIGHT);
}

AnkrDecay::~AnkrDecay() {
    shutdown();
}

void AnkrDecay::init(const std::string &title, const int width, const int height) {
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize!" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        isValid = false;
        return;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window could not be created!" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        isValid = false;
        return;
    }

    if (SDL_Surface* icon = IMG_Load(R"(C:\software\Cpp\projects\Ankr\Assets\images\logo\ankr_logo.jpg)")) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    } else {
        std::cout << "Failed to load window icon!" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created!" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        isValid = false;
        return;
    }

    physics_manager_ = std::make_unique<PhysicsManager>();
    physics_manager_->Init(100.0f, 0.0f, 0.0f);

    image_loader_ = std::make_unique<ImageLoader>(renderer);

    audio_manager_ = std::make_unique<AudioManager>();
    audio_manager_->playMusic("main_theme", R"(C:\software\Cpp\projects\Ankr\Assets\music\mixkit-driving-ambition-32.mp3)");

    input_manager_ = std::make_unique<InputManager>();

    ankr_board_ =  std::make_unique<AnkrBoard>(image_loader_.get());
    ankr_board_->loadMapTex(R"(C:\software\Cpp\projects\Ankr\Assets\images\map\ankr_map.jpeg)");

    ankr_debug_ = std::make_unique<AnkrDebug>(renderer);
    ankr_debug_->init(window);

    /* === Animation System Placeholder ===
    animation_clip_.texture = image_loader_->loadTexture(R"(C:\software\Cpp\projects\Ankr\Assets\images\characters\animation\ability_an.png)");
    animation_clip_.FPS = TARGET_FPS;

    animation_sprite_->setClip(&animation_clip_);
    animation_sprite_->play();
    animation_system_->Add(animation_sprite_.get());
    */
    isValid = true;
}

void AnkrDecay::InitObject() {

    const vec2D pos_h {50.f/ppm, 50.f/ppm};
    entity_d _hero {
        physics_manager_->initializeBox(static_cast<float>(SCREEN_WIDTH)/2/ppm, (static_cast<float>(SCREEN_HEIGHT)-20.f)/ppm, pos_h.posX, pos_h.posY, true),
        image_loader_->loadTexture(R"(C:\software\Cpp\projects\Ankr\Assets\images\characters\test\GitHub.png)")
    };
    auto hero = std::make_unique<Aether>(_hero.body, pos_h.posX, pos_h.posY, _hero.texture, physics_manager_.get());
    heroes_.push_back(std::move(hero));

    const vec2D pos_v {100.f/ppm, 70.f/ppm};
    entity_d _villain {
        physics_manager_->initializeBox(static_cast<float>(SCREEN_WIDTH)/2/ppm, (static_cast<float>(SCREEN_HEIGHT)-20.f)/ppm, pos_v.posX, pos_v.posY, true),
        image_loader_->loadTexture(R"(C:\software\Cpp\projects\Ankr\Assets\images\characters\test\chibi.png)")
    };
    auto villain = std::make_unique<DarkKnight>(_villain.body, pos_v.posX, pos_v.posY, _villain.texture, physics_manager_.get());
    villains_.push_back(std::move(villain));

}

void AnkrDecay::CleanObject() {
    std::erase_if(heroes_,
                  [](const std::unique_ptr<heroes::Champions>& hero) {
                      return !hero->isAlive();
                  }
    );

    std::erase_if(villains_,
                  [](const std::unique_ptr<villains::Champions>& villain) {
                      return !villain->isAlive();
                  }
    );
}

void AnkrDecay::run() {
    InitObject();

    Uint64 fpsNow = SDL_GetPerformanceCounter();
    const Uint64 freq = SDL_GetPerformanceFrequency();

    while (isValid) {
        const Uint64 fpsNext = SDL_GetPerformanceCounter();
        const float deltaTime = static_cast<float>(fpsNext - fpsNow) / static_cast<float>(freq);
        fpsNow = fpsNext;

        const Uint32 currentTicks = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isValid = false;
            ankr_debug_->handleEvent(event);
            input_manager_->handleEvent(event);
        }

        input_manager_->update();
        Update(deltaTime);
        Render();

        ankr_debug_->newFrame();
        ankr_debug_->displayGUI();
        ankr_debug_->render();

        if (const Uint32 elapsed = SDL_GetTicks() - currentTicks; elapsed < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - elapsed);
        }

        SDL_RenderPresent(renderer);
    }
}

void AnkrDecay::shutdown() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (ankr_debug_) ankr_debug_->shutdown();
    SDL_Quit();
    isValid = false;
}

void AnkrDecay::Render() const {
    SDL_SetRenderDrawColor(renderer, 52, 152, 219, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    ankr_board_->drawBoard(renderer);

    for (const auto& it : heroes_) {
        it->render(renderer, ppm, SCREEN_WIDTH, SCREEN_HEIGHT);
        ankr_debug_->setHero(it.get());
        //animation_sprite_->render(renderer, static_cast<int>(it->getWidth()), static_cast<int>(it->getHeight()));
    }

    for (const auto& it : villains_) {
        it->render(renderer, ppm, SCREEN_WIDTH, SCREEN_HEIGHT);
        ankr_debug_->setVillain(it.get());
        //animation_sprite_->render(renderer, static_cast<int>(it->getWidth()), static_cast<int>(it->getHeight()));
    }
}

void AnkrDecay::Update(const float deltaTime) {

    if (heroes_.empty() || villains_.empty()) {
        CleanObject();
        GameOver();
        return;
    }

    entity_t hero_{
        heroes_[0].get(),
        heroes_[0]->getBody(),
        {0.0f, 0.0f},
        0
    };

    entity_t villain_{
        villains_[0].get(),
        villains_[0]->getBody(),
        {0.0f, 0.0f},
        0
    };

    constexpr float speed = 15.0f;

    hero_.velocity = {0.0f, 0.0f};
    villain_.velocity = {0.0f, 0.0f};

    if (input_manager_->isPressed(SDL_SCANCODE_D)) hero_.velocity.posX = speed;
    if (input_manager_->isPressed(SDL_SCANCODE_A)) hero_.velocity.posX = -speed;
    if (input_manager_->isPressed(SDL_SCANCODE_W)) hero_.velocity.posY = speed;
    if (input_manager_->isPressed(SDL_SCANCODE_S)) hero_.velocity.posY = -speed;

    if (input_manager_->isPressed(SDL_SCANCODE_RIGHT)) villain_.velocity.posX = speed;
    if (input_manager_->isPressed(SDL_SCANCODE_LEFT)) villain_.velocity.posX = -speed;
    if (input_manager_->isPressed(SDL_SCANCODE_UP)) villain_.velocity.posY = speed;
    if (input_manager_->isPressed(SDL_SCANCODE_DOWN)) villain_.velocity.posY = -speed;

    if (input_manager_->isTriggered(SDL_SCANCODE_Z)) hero_.aIndex = 1;
    else if (input_manager_->isTriggered(SDL_SCANCODE_X)) hero_.aIndex = 2;
    else hero_.aIndex = 0;

    if (input_manager_->isTriggered(SDL_SCANCODE_M)) villain_.aIndex = 1;
    else if (input_manager_->isTriggered(SDL_SCANCODE_N)) villain_.aIndex = 2;
    else villain_.aIndex = 0;

    if (hero_.aIndex != 0 && hero_.ptr->isUsingAbility() == false) {
        hero_.ptr->useAbility(villain_.ptr, hero_.aIndex);
        // animation_system_->Update(deltaTime); // animation
        std::cout << hero_.ptr->getName() << " used Ability " << hero_.aIndex << " on " << villain_.ptr->getName() << std::endl;
        hero_.ptr->setUsingAbility(true);
    }

    if (input_manager_->isTriggered(SDL_SCANCODE_0)) hero_.ptr->setUsingAbility(false);

    if (villain_.aIndex != 0 && villain_.ptr->isUsingAbility() == false) {
        villain_.ptr->useAbility(hero_.ptr, villain_.aIndex);
        // animation_system_->Update(deltaTime); // animation
        std::cout << villain_.ptr->getName() << " used Ability " << hero_.aIndex << " on " << hero_.ptr->getName() << std::endl;
        villain_.ptr->setUsingAbility(true);
    }

    if (input_manager_->isTriggered(SDL_SCANCODE_9)) villain_.ptr->setUsingAbility(false);

    Move(hero_.body, hero_.velocity.posX, hero_.velocity.posY);
    Move(villain_.body, villain_.velocity.posX, villain_.velocity.posY);

    physics_manager_->calculateCollision(hero_.body, hero_.ptr->getWidth(), hero_.ptr->getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT);
    physics_manager_->calculateCollision(villain_.body, villain_.ptr->getWidth(), villain_.ptr->getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!hero_.ptr->isAlive()) {
        std::cout << hero_.ptr->getName() << " has been defeated!" << std::endl;
    } else if (!villain_.ptr->isAlive()) {
        std::cout << villain_.ptr->getName() << " has been defeated!" << std::endl;
    }

    CleanObject();

    physics_manager_->Step(deltaTime, 8, 3);
}

void AnkrDecay::GameOver() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

    std::cout << "Ankr Decay is Over. Thanks for playing." << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    isValid =  false;
    std::cin.get();
}

void AnkrDecay::Move(b2Body *body, const float velX, const float velY) {
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = velX;
    velocity.y = velY;
    body->SetLinearVelocity(velocity);
}

bool AnkrDecay::isRunning() const {
    return isValid;
}
