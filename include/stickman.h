#ifndef STICKMAN_H
#define STICKMAN_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "gameobject.h"
#include "animation.h"
#include "position.h"
#include "vector2d.h"
#include "exceptions.h"

class StickmanAnimation: public Animation {
    Position* pos;
    SDL_Rect source{0,0,WIDTH,HEIGHT}, destination{0,0,WIDTH,HEIGHT};
    SDL_Texture* bmp_texture;
    static const int WIDTH, HEIGHT, DELAY;
    int i{0};
public:
    StickmanAnimation(Position* p): Animation(DELAY, p) {}
    ~StickmanAnimation() {
        if(bmp_texture != nullptr) SDL_DestroyTexture(bmp_texture);
    }
    void load_media(SDL_Renderer* gRenderer) override {
        std::string file = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/stickman.bmp";
        SDL_Surface* bmp_surface = SDL_LoadBMP(file.c_str());
        if(bmp_surface == nullptr) {
            auto msg = std::string{SDL_GetError()};
            throw SDL_Cannot_Load_Media(file, msg);
        }
        bmp_texture = SDL_CreateTextureFromSurface(gRenderer, bmp_surface);
        std::cout << "bmp texture loaded" << std::endl;
        SDL_FreeSurface(bmp_surface);
    }
    void render(SDL_Renderer* gRenderer) override {
        if(bmp_texture == nullptr) load_media(gRenderer);
        auto flip_status = SDL_FLIP_NONE;
        if(to_flip()) flip_status = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(gRenderer, bmp_texture, &source, &destination, 0, 0, flip_status);
    }
    void update() override {
        if(is_suspended() || !to_update()) return;
        auto x = i % 4;
        auto y = i / 4;
        i = (i + 1) % 8;
        source.x = x*WIDTH;
        source.y = y*HEIGHT;
        Vector2D coord = position()->get_coord();
        destination.x = coord.x;
        destination.y = coord.y;
    }
};

class StickmanController: public Controller {
public:
    StickmanController(Position* p, Animation* a): Controller(p,a) {
        add_keyboard_input(SDL_SCANCODE_W, [p,a] (bool& quit) {
            std::cout << "up key is pressed" << std::endl;
            if(!a->is_suspended()) {
                auto v = p->get_velocity();
                if(v.y > 0) p->set_velocity(v.x, -v.y);
            }
        });
        add_keyboard_input(SDL_SCANCODE_S, [p,a] (bool& quit) {
            std::cout << "down key is pressed" << std::endl;
            if(!a->is_suspended()) {
                auto v = p->get_velocity();
                if(v.y < 0) p->set_velocity(v.x, -v.y);
            }
        });
        add_keyboard_input(SDL_SCANCODE_A, [p,a] (bool& quit) {
            std::cout << "left key is pressed" << std::endl;
            if(!a->is_suspended()) {
                auto v = p->get_velocity();
                if(v.x > 0) {
                    p->set_velocity(-v.x, v.y);
                    a->toggle_flip();
                }
            }
        });
        add_keyboard_input(SDL_SCANCODE_D, [p,a] (bool& quit) {
            std::cout << "right key is pressed" << std::endl;
            if(!a->is_suspended()) {
                auto v = p->get_velocity();
                if(v.x < 0) {
                    p->set_velocity(-v.x, v.y);
                    a->toggle_flip();
                }
            }
        });

        add_keyboard_input(SDL_SCANCODE_SPACE, [p,a] (bool& quit) {
            std::cout << "pause key is pressed" << std::endl;
            if(a->is_suspended()) {
                a->unsuspend();
                p->unsuspend();
            } else {
                a->suspend();
                p->suspend();
            }
        });
    }
};

class Stickman: public GameObject {
public:
    static const int WIDTH, HEIGHT, DELAY;
    Stickman(Position* p, Animation* a, Controller* c): GameObject{p,a,c} {}
    Stickman(double x, double y): GameObject(x,y,WIDTH,HEIGHT) {
        auto p = position();
        p->set_velocity(2,2);
        set_animation(new StickmanAnimation(p));
        auto a = animation();
        set_controller(new StickmanController(p,a));
    }
    ~Stickman() {
        delete animation();
        delete controller();
    }
};

const int Stickman::WIDTH = 400, Stickman::HEIGHT = 366;

const int StickmanAnimation::WIDTH = 400, StickmanAnimation::HEIGHT = 366, StickmanAnimation::DELAY = 2;

#endif
