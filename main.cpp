#include "animation.h"
#include "exceptions.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Animation anime{};
        anime.main_loop();
    } catch(SDL_Cannot_Init& e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch(SDL_Cannot_Load_Media& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    std::cout << "program exiting" << std::endl;
    return 0;
}

