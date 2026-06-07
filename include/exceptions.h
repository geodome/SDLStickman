#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class myexception: public std::exception {
    std::string message;
public:
    myexception(char* msg): message{std::string{msg}} {};
    myexception(std::string msg): message{std::move(msg)} {};
    myexception(std::string tag, std::string msg):
        message{std::format("{} : {}", tag, msg)} {}
    myexception(std::string tag, char* msg):
        message{std::format("{} : {}", tag, std::string{msg})} {}
    std::string what() {
        return message;
    }
};

class SDL_Cannot_Init: public myexception {
public:
    SDL_Cannot_Init(std::string msg):
    myexception("SDL Cannot Init", msg) {};
    SDL_Cannot_Init(char* msg):
    myexception("SDL Cannot Init", msg) {};
};

class SDL_Cannot_Load_Media: public myexception {
    SDL_Cannot_Load_Media(char* file, std::string msg):
    myexception(
                "SDL Cannot Load Media",
                std::format("{} : {}", std::string{file}, msg)
    ) {};
    SDL_Cannot_Load_Media(char* file, char* msg):
    myexception(
                "SDL Cannot Load Media",
                std::format("{} : {}", std::string{file},std::string{msg})
    ) {};
};

#endif
