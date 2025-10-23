#include <iostream>
#include "MindEngine/Game/main/decay.hpp"

int main(int argc, char* argv[]) {
    try {
        if (AnkrDecay game; game.isRunning()) {
            game.run();
        } else {
            std::cerr << "Game couldn't start." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Game exited successfully." << std::endl;
    return EXIT_SUCCESS;
}
