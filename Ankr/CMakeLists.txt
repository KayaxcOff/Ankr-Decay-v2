cmake_minimum_required(VERSION 3.20)
project(Ankr)

set(CMAKE_CXX_STANDARD 20)

set(SDL_DIR "C:\\software\\Cpp\\libraries\\SDL2-2.32.6")
include_directories("${SDL_DIR}\\include")
link_directories("${SDL_DIR}\\lib\\x64")

set(BOX2D_DIR "C:\\software\\Cpp\\libraries\\Box2D\\box2d-2.4.1")
include_directories("${BOX2D_DIR}\\include")
link_directories("${BOX2D_DIR}\\build\\bin\\Debug")

#set(NLOHMANN "C:\\software\\Cpp\\libraries\\json-3.12.0\\json-3.12.0")
#include_directories("${NLOHMANN}\\include")

set(IMGUI_DIR "C:\\software\\Cpp\\libraries\\imgui-1.92.1")
include_directories("${IMGUI_DIR}")
include_directories("${IMGUI_DIR}\\backends")

set(IMGUI
        "C:\\software\\Cpp\\libraries\\imgui-1.92.1\\imgui.cpp"
        "C:\\software\\Cpp\\libraries\\imgui-1.92.1\\imgui_draw.cpp"
        "C:\\software\\Cpp\\libraries\\imgui-1.92.1\\imgui_tables.cpp"
        "C:\\software\\Cpp\\libraries\\imgui-1.92.1\\imgui_widgets.cpp"
        "C:\\software\\Cpp\\libraries\\imgui-1.92.1\\backends\\imgui_impl_sdl2.cpp"
        "C:\\software\\Cpp\\libraries\\imgui-1.92.1\\backends\\imgui_impl_sdlrenderer2.cpp"
)

add_definitions(-DSDL_MAIN_HANDLED)

add_executable(Ankr main.cpp
        MindEngine/Game/main/decay.hpp
        MindEngine/Game/main/decay.cpp
        MindEngine/Game/define_character/base_character.hpp
        MindEngine/Game/define_character/base/hero_base.hpp
        MindEngine/Game/define_character/base/villain_base.hpp
        MindEngine/Game/define_character/characters/heroes.hpp
        MindEngine/Game/define_character/characters/heroes.cpp
        MindEngine/Game/define_character/bots/villains.hpp
        MindEngine/Game/define_character/bots/villains.cpp
        MindEngine/Core/debug/ankr_debug.hpp
        MindEngine/Core/debug/ankr_debug.cpp
        MindEngine/Game/board/game_map.hpp
        MindEngine/Game/board/game_map.cpp
        MindEngine/Core/player_inputs/input_manager.hpp
        MindEngine/Core/player_inputs/input_manager.cpp
        MindEngine/Core/physics_rules/physics_manager.hpp
        MindEngine/Core/physics_rules/physics_manager.cpp
        MindEngine/Core/graphics/object/object_system.hpp
        MindEngine/Core/graphics/object/object_system.cpp
        #MindEngine/Core/graphics/animation/animation_system.hpp
        #MindEngine/Core/graphics/animation/animation_system.cpp
        MindEngine/Asset/image/game_images.hpp
        MindEngine/Asset/image/game_images.cpp
        MindEngine/Asset/sound/game_music.hpp
        MindEngine/Asset/sound/game_music.cpp

        ${IMGUI}
)

target_link_libraries(Ankr
        "${SDL_DIR}\\lib\\x64\\SDL2.lib"
        "${SDL_DIR}\\lib\\x64\\SDL2_image.lib"
        "${SDL_DIR}\\lib\\x64\\SDL2_ttf.lib"
        "${SDL_DIR}\\lib\\x64\\SDL2_mixer.lib"
        "${BOX2D_DIR}\\build\\bin\\Debug\\box2d.lib"
)