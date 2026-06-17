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
    SDL_Rect source, destination;
    SDL_Texture* bmp_texture = nullptr;
    double width, height;
    int i{0};
public:
    StickmanAnimation(Position* p): Animation{p} {
        width = p->get_width() - 2;
        height = p->get_height() - 2;
        source.w = width;
        source.h = height;
        destination.w = width;
        destination.h = height;
    }
    ~StickmanAnimation() {
        if(bmp_texture != nullptr) SDL_DestroyTexture(bmp_texture);
    }
    void set_position(Position* p) {
        pos = p;
    }
    void load_media(SDL_Renderer* gRenderer) override {
        std::string file = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/stickman.bmp";
        SDL_Surface* bmp_surface = SDL_LoadBMP(file.c_str());
        if(bmp_surface == nullptr) {
            auto msg = std::string{SDL_GetError()};
            throw SDL_Cannot_Load_Media(file, msg);
        }
        bmp_texture = SDL_CreateTextureFromSurface(gRenderer, bmp_surface);
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
        source.x = x*width+1;
        source.y = y*height+1;
        Vector2D coord = position()->get_coord();
        destination.x = coord.x;
        destination.y = coord.y;
    }
};

class StickmanController: public Controller {
public:
    StickmanController(Position* p, Animation* a): Controller(p,a) {
        auto up = SDL_SCANCODE_W;
        auto down = SDL_SCANCODE_S;
        auto left = SDL_SCANCODE_A;
        auto right = SDL_SCANCODE_D;
        auto pause = SDL_SCANCODE_SPACE;
        
        add_keyboard_input(up, [p,a] (bool& quit) {
            std::cout << "up key is pressed" << std::endl;
            if(!a->is_suspended()) {
                auto v = p->get_velocity();
                if(v.y > 0) p->set_velocity(v.x, -v.y);
            }
        });
        add_keyboard_input(down, [p,a] (bool& quit) {
            std::cout << "down key is pressed" << std::endl;
            if(!a->is_suspended()) {
                auto v = p->get_velocity();
                if(v.y < 0) p->set_velocity(v.x, -v.y);
            }
        });
        add_keyboard_input(left, [p,a] (bool& quit) {
            std::cout << "left key is pressed" << std::endl;
            if(!a->is_suspended()) {
                auto v = p->get_velocity();
                if(v.x > 0) {
                    p->set_velocity(-v.x, v.y);
                    a->toggle_flip();
                }
            }
        });
        add_keyboard_input(right, [p,a] (bool& quit) {
            std::cout << "right key is pressed" << std::endl;
            if(!a->is_suspended()) {
                auto v = p->get_velocity();
                if(v.x < 0) {
                    p->set_velocity(-v.x, v.y);
                    a->toggle_flip();
                }
            }
        });

        add_keyboard_input(pause, [p,a] (bool& quit) {
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
    Position p{0,0,WIDTH,HEIGHT};
    StickmanAnimation a{&p};
    StickmanController c{&p,&a};
public:
    static const double WIDTH, HEIGHT;
    static const int DELAY;
    Stickman(double x, double y, uint32_t d) {
        p.set_velocity(2,2);
        p.set_coord(x,y);
        a.set_delay(d);
    }
    Position* position() override {
        return &p;
    }
    Animation* animation() override {
        return &a;
    }
    Controller* controller() override {
        return &c;
    }
};

const double Stickman::WIDTH = 400, Stickman::HEIGHT = 344;

#endif
