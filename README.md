# Ankr:Decay - v2.0

## Mind Engine (C++)

The game engine part of the project is developed in C++. It relies on the following libraries:

- SDL2 (v2.32.6)  
- SDL2-Image  
- SDL2-Mixer  
- SDL2-TTF  
- Box2D (v2.4.1)  
- ImGUI (v1.92.1)  

Characters are defined by object properties such as body, texture, and position. Accordingly, character classes inherit from the `Object2D` base class, while character-specific properties are managed in the `BaseCharacter` class. To create a Box2D `b2Body`, the `initializeBox` function from the `PhysicsManager` is used.

Example usage:

```cpp
std::unique_ptr<PhysicsManager> physics_manager_ = std::make_unique<PhysicsManager>();
b2Body* body = physics_manager_->initializeBox(110.f, 225.f, 50.f, 50.f, false);
```
Characters require health and abilities, which are implemented in the base character classes. To represent characters, the following struct template is used:
``` cpp
template<typename T>
struct entity_t {
    T *ptr;
    b2Body *body;
    vec2D velocity;
    int aIndex;
};
```
The `InputManager’s` `isPressed` function checks key inputs multiple times (6 times), which causes issues when using abilities. Therefore, an `isTriggered` function was introduced to handle this more efficiently.

One of the main challenges was managing the game loop, especially regarding ability usage. To address this, character classes implement boolean functions to control abilities and prevent the program from entering infinite loops.

# Mind Launcher (Java)

The launcher for Ankr:Decay is developed using JavaFX. It features two main views: one for launching and playing the game, and another for reading information about the game.
