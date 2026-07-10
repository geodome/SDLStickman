#ifndef GLOBAL_H
#define GLOBAL_H

class Global {
public:
    static const size_t ROWS, COLS;
    static const int LL, UL, UNIT, WINDOW_WIDTH, WINDOW_HEIGHT;
};

const size_t Global::COLS = 24, Global::ROWS = 12;
const int Global::LL = 4, Global::UL = 20, Global::UNIT = 64;
const int Global::WINDOW_WIDTH = 24*Global::UNIT;
const int Global::WINDOW_HEIGHT = 12*Global::UNIT;

#endif
