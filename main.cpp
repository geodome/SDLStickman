#include <iostream>
#include "exceptions.h"
#include "system.h"

int main(int argc, char* argv[]) {
    try {
        auto s = System(1200,600);
        s.start_demo();
    } catch(SDL_Cannot_Init& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(SDL_Cannot_Load_Media& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
