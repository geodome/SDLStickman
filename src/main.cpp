#include <iostream>
#include "exceptions.h"
#include "system.h"

#ifndef TEST_MODE

int main(int argc, char* argv[]) {
    try {
        auto s = System();
        s.main_loop();
    } catch(SDL_Cannot_Init& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch(SDL_Cannot_Load_Media& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

#endif

#ifdef TEST_MODE

#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif
