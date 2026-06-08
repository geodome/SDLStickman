#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>
#include <vector>
#include <functional>
#include <string>
#include <SDL2/SDL.h>
#include "exceptions.h"

class GameObject {
    std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&, bool&)>>> handlers{};
protected:
    uint32_t ticker{0}, delay{1};
public:
    GameObject() = default;
    void tick();
    void reset_ticker();
    bool to_update();
    virtual ~GameObject() = default;
    virtual void update() {};
    virtual void render(SDL_Renderer*) {};
    void add_handler(uint32_t, std::function<void(SDL_Event,bool&, bool&)>);
    const std::map<uint32_t, std::vector<std::function<void(SDL_Event,bool&, bool&)>>> get_handlers();
};

class Stickman: public GameObject {
    uint32_t i{0};
    SDL_Texture* bmp_texture;
    SDL_Rect source{0,0,WIDTH,HEIGHT}, destination{0,0,WIDTH,HEIGHT};
    bool suspended{false};
public:
    static const int WIDTH{400}, HEIGHT{366};
    Stickman(int x, int y, uint32_t delay_ticks);
    ~Stickman();
    void reset_frame();
    void next_frame();
    void update() override;
    void render(SDL_Renderer*) override;
    void toggle_animation();
    void load_media(SDL_Renderer*);
};

#endif



