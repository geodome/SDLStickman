#include "system.h"
#include "exceptions.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        System anime{};
        anime.main_loop();
    } catch(SDL_Cannot_Init& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(SDL_Cannot_Load_Media& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    std::cout << "program exiting" << std::endl;
    return 0;
}

