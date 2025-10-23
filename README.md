# Ankr:Decay - v2.0

## Ankr-Decay

The game engine portion of the project was written in C++. Here are the necessary libraries:
- SDL2-2.32.6
- SDL2-Image
- SDL2-Mixer
- SDL2-TTF
- Box2D-2.4.1
- ImGUI-1.92.1

To create a character, that character needs object properties (body, texture, position), so character classes inherit from the Object2D class. Character properties come from the BaseCharacter class. To create a b2Body, I used initializeBox function from PhysicsManager.
Simple example:
'''
std::unique_ptr<PhysicsManager> physics_manager_ = std::make_unique<PhysicsManager>();
b2Body* body = physics_manager_->initializeBox(110.f, 225.f, 50.f, 50.f, false);
'''

For a character to be a character, it must have health and abilities. I added these to the base character classes and for define characters, I created a struct:
'''
template<typename T>
    struct entity_t {
        T *ptr;
        b2Body *body;
        vec2D velocity;
        int aIndex;
    };
'''

## Mind Launcher

I used JavaFX for create a Launcher for Ankr:Decay.
