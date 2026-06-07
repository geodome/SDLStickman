#include "animation.h"
#include "exception.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Animation anime{};
        anime.main_loop();
    } catch(SDL_Cannot_Init& e) {
        std::cout << e.what() << std::endl;
    } catch(SDL_Cannot_Load_Media& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "Program exiting" << std::endl;
}
