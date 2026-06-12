#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <functional>
#include <vector>
#include <format>
#include <SDL2/SDL.h>
#include "exceptions.h"
#include "gameobject.h"

namespace System {

class Game {
    int WIDTH, HEIGHT;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&,bool&)>>> handlers{};
    std::vector<GameObjects::GameObject*> gObjects;
    static Game* instance;
    Game();
    friend Game* Singleton();
    friend void Destroy_Singleton();
public:
    static const int DELAY;
    ~Game();
    void main_loop();
    void register_handler(uint32_t, std::function<void(SDL_Event, bool&, bool&)>);
    void handle_events(bool&, bool&);
    void tick();
    void update();
    void render();
    void add_game_object(GameObjects::GameObject*);
};

Game* Singleton();;
void Destroy_Singleton();

}
#endif
