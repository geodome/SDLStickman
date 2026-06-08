#include "animation.h"
#include "exceptions.h"
#include <iostream>
//#include <SDL2/SDL.h>


int main(int argc, char* argv[]) {
    // std::cout << SDL_Init(SDL_INIT_VIDEO) << std::endl;
    try {
        Animation anime{};
        anime.main_loop();
        //std::cout << "hello world\n";
    } catch(SDL_Cannot_Init& e) {
        std::cout << e.what() << std::endl;
    } catch(SDL_Cannot_Load_Media& e) {
        std::cout << e.what() << std::endl;
    }
}

