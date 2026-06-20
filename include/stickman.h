#ifndef STICKMAN2_H
#define STICKMAN2_H

#include <format>
#include <memory>
#include <SDL2/SDL.h>
#include "eventemitter.h"
#include "uuid.h"
#include "gameobject.h"
#include "exceptions.h"
#include "sprite.h"
#include "vector2d.h"

class StickmanSprite: public Sprite {
public:
    SDL_Texture* bmp_texture = nullptr;
    SDL_Rect source, destination;
    SDL_RendererFlip flip_status = SDL_FLIP_NONE;
    int i{0};

    StickmanSprite(int width, int height): Sprite{4} {
        source.w = width;
        source.h = height;
        destination.w = width;
        destination.h = height;
    }
    
    void load_media(SDL_Renderer* gRenderer) {
        if(bmp_texture != nullptr) return;
        std::string file = "/Users/donaldsontan/Projects/mtd215/mtd215/assets/stickman.bmp";
        SDL_Surface* bmp_surface = SDL_LoadBMP(file.c_str());
        if(bmp_surface == nullptr) {
            auto msg = std::string{SDL_GetError()};
            throw SDL_Cannot_Load_Media(file, msg);
        }
        bmp_texture = SDL_CreateTextureFromSurface(gRenderer, bmp_surface);
        SDL_FreeSurface(bmp_surface);
    }
    
    void next_frame(Position& p) {
        destination.x = p.coord.x;
        destination.y = p.coord.y;
        source.x = (i % 4) * source.w;
        source.y = (i / 4) * source.h;
        i = (i + 1) % 8;
    }
    
    ~StickmanSprite() {
        if(bmp_texture == nullptr) return;
        SDL_DestroyTexture(bmp_texture);
        bmp_texture = nullptr;
    }
};


class Stickman: public GameObject {
    std::string is_up_key, is_down_key, is_left_key, is_right_key, is_pause_key, is_quit_key;
    std::string update_sprite, render_sprite, tick_sprite, tick_position;
public:
    static const int WIDTH, HEIGHT;
    Position position{0,0,0,0,0,0};
    StickmanSprite sprite{Stickman::WIDTH, Stickman::HEIGHT};
    
    Stickman(double x, double y, double vx, double vy): GameObject() {
        position.coord = {x,y};
        position.velocity = {vx, vy};
        
        if(vx < 0) sprite.flip_status = SDL_FLIP_HORIZONTAL;

        add_input_handlers();
        add_system_handlers();
    }
    
    void add_input_handlers() override {
        auto up = SDL_SCANCODE_W;
        auto down = SDL_SCANCODE_S;
        auto left = SDL_SCANCODE_A;
        auto right = SDL_SCANCODE_D;
        auto pause = SDL_SCANCODE_SPACE;
        auto quit = SDL_SCANCODE_Q;

        is_up_key = std::format("is_up_key for Stickman {}", uuid);
        EventEmitter::key_down->then(is_up_key, [this,up] (const SDL_Scancode& sc) {
            if(sc != up) return false;
            std::cout << "up key is pressed" << std::endl;
            if(this->suspended || this->position.velocity.y <= 0) return false;
            this->position.velocity.y = - this->position.velocity.y;
            return true;
        });
        
        is_down_key = std::format("is_down_key for stickman {}", uuid);
        EventEmitter::key_down->then(is_down_key, [this,down] (const SDL_Scancode& sc) {
            if(sc != down) return false;
            std::cout << "down key is pressed" << std::endl;
            if(this->suspended || this->position.velocity.y >= 0) return false;
            this->position.velocity.y = - this->position.velocity.y;
            return true;
        });
        
        is_left_key = std::format("is_left_key for Stickman {}", uuid);
        EventEmitter::key_down->then(is_left_key, [this,left] (const SDL_Scancode& sc) {
            if(sc != left) return false;
            std::cout << "left key is pressed" << std::endl;
            if(this->suspended || this->position.velocity.x <= 0) return false;
            this->position.velocity.x = - this->position.velocity.x;
            this->sprite.flip_status = SDL_FLIP_HORIZONTAL;
            return true;
        });

        is_right_key = std::format("is_right_key for Stickman {}",uuid);
        EventEmitter::key_down->then(is_right_key, [this,right] (const SDL_Scancode& sc) {
            if(sc != right) return false;
            std::cout << "right key is pressed" << std::endl;
            if(this->suspended || this->position.velocity.x >= 0) return false;
            this->position.velocity.x = - this->position.velocity.x;
            this->sprite.flip_status = SDL_FLIP_NONE;
            return true;
        });

        is_pause_key = std::format("is_pause_key for Stickman {}", uuid);
        EventEmitter::key_down->then(is_pause_key, [this,pause] (const SDL_Scancode& sc) {
            if(sc!=pause) return false;
            std::cout << "pause key is pressed" << std::endl;
            this->suspended = ! this->suspended;
            return true;
        });
        
        is_quit_key = std::format("is_quit_key for Stickman {}", uuid);
        EventEmitter::key_down->then(is_quit_key, [this, quit] (const SDL_Scancode& sc) {
            if(sc != quit) return false;
            std::cout << "quit key is pressed" << std::endl;
            EventEmitter::system_quit->notify(true);
            return true;
        });
    }
    
    void add_system_handlers() override {
        update_sprite = std::format("update_sprite for Stickman {}", uuid);
        EventEmitter::system_update->then(update_sprite, [this] (const bool&) {
            if(this->suspended || !this->sprite.to_update()) return false;
            this->sprite.next_frame(this->position);
            return true;
        });

        render_sprite = std::format("render_sprite for Stickman {}", uuid);
        EventEmitter::system_render->then(render_sprite, [this] (SDL_Renderer* gRenderer) {
            if(this->suspended) return false;
            this->sprite.load_media(gRenderer);
            SDL_RenderCopyEx(gRenderer, this->sprite.bmp_texture, &this->sprite.source, &this->sprite.destination, 0, 0, this->sprite.flip_status);
            return true;
        });
        
        tick_sprite = std::format("tick_sprite for {}", uuid);
        EventEmitter::system_tick->then(tick_sprite, [this] (const bool&) {
            if(this->suspended) return false;
            this->sprite.tick();
            return true;
        });

        tick_position = std::format("tick_position for Stickman {}", uuid);
        EventEmitter::system_tick->then(tick_position, [this] (const bool&) {
            if(this->suspended) return false;
            this->position.tick();
            return true;
        });

    }
    ~Stickman() {
        EventEmitter::system_tick->erase(tick_position);
        EventEmitter::system_tick->erase(tick_sprite);
        EventEmitter::system_render->erase(render_sprite);
        EventEmitter::key_down->erase(is_up_key);
        EventEmitter::key_down->erase(is_down_key);
        EventEmitter::key_down->erase(is_left_key);
        EventEmitter::key_down->erase(is_right_key);
        EventEmitter::key_down->erase(is_pause_key);
        EventEmitter::key_down->erase(is_quit_key);
    }
};

const int Stickman::WIDTH = 400, Stickman::HEIGHT = 344;

#endif

