#include <iostream>
#include "exceptions.h"
#include "system.h"

int main(int argc, char* argv[]) {
    
    try {
        System::Singleton()->main_loop();
        System::Destroy_Singleton();
    } catch(System::SDL_Cannot_Init& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(GameObjects::SDL_Cannot_Load_Media& e) {
        std::cerr << e.what() << std::endl;
        SDL_Quit();
        return 1;
    }
    return 0;
    
}

