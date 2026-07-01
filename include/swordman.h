#ifndef SWORDMAN_H
#define SWORDMAN_H

#include <string>
#include <iostream>
#include <format>
#include <SDL2/SDL_render.h>
#include <SDL2_image/SDL_image.h>
#include "entity.h"

enum SwordmanState {
    ARMED_IDLE_FORWARD,
    ARMED_IDLE_BACKWARD,
    ARMED_WALK_FORWARD,
    ARMED_WALK_BACKWARD,
    ARMED_CLIMB_UP,
    ARMED_CLIMB_DOWN,
    ARMED_ATTACK_IDLE_FORWARD,
    ARMED_ATTACK_IDLE_BACKWARD,
    ARMED_ATTACK_WALK_FORWARD,
    ARMED_ATTACK_WALK_BACKWARD,
    UNARMED_IDLE_FORWARD,
    UNARMED_IDLE_BACKWARD,
    UNARMED_WALK_FORWARD,
    UNARMED_WALK_BACKWARD,
    UNARMED_CLIMB_UP,
    UNARMED_CLIMB_DOWN,
};

class Swordman: public Entity {
    static const int SOURCE_WIDTH, SOURCE_HEIGHT, DEST_WIDTH, DEST_HEIGHT;
    static const double UNIT;
    static const uint32_t PERIOD;
    SDL_Rect source{0,0,Swordman::SOURCE_WIDTH, Swordman::SOURCE_HEIGHT}, dest{0,0,Swordman::DEST_WIDTH, Swordman::DEST_HEIGHT};
    SDL_Texture* current;
    SDL_Texture* armed_idle[8];
    SDL_Texture* armed_walk[8];
    SDL_Texture* armed_attack[11];
    SDL_Texture* armed_climb[4];
    SDL_Texture* unarmed_idle[8];
    SDL_Texture* unarmed_walk[8];
    SDL_Texture* unarmed_climb[4];
    uint32_t ticker = 0, sprite_ticker = 0, attack_queue = 0;
    SDL_RendererFlip flip;
    bool loaded = false;
    SwordmanState state;
    void set_state(SwordmanState s) {
        int vx = 2*Swordman::UNIT;
        switch(s) {
            case UNARMED_IDLE_FORWARD:
            case ARMED_ATTACK_IDLE_FORWARD:
            case ARMED_IDLE_FORWARD:
                state = s;
                flip = SDL_FLIP_NONE;
                position.velocity.x = 0;
                position.velocity.y = 0;
                break;
            case UNARMED_IDLE_BACKWARD:
            case ARMED_ATTACK_IDLE_BACKWARD:
            case ARMED_IDLE_BACKWARD:
                state = s;
                flip = SDL_FLIP_HORIZONTAL;
                position.velocity.x = 0;
                position.velocity.y = 0;
                break;
            case UNARMED_WALK_FORWARD:
            case ARMED_ATTACK_WALK_FORWARD:
            case ARMED_WALK_FORWARD:
                state = s;
                flip = SDL_FLIP_NONE;
                position.velocity.x = vx;
                position.velocity.y = 0;
                break;
            case UNARMED_WALK_BACKWARD:
            case ARMED_ATTACK_WALK_BACKWARD:
            case ARMED_WALK_BACKWARD:
                state = s;
                flip = SDL_FLIP_HORIZONTAL;
                position.velocity.x = -vx;
                position.velocity.y = 0;
                break;
            case UNARMED_CLIMB_UP:
            case ARMED_CLIMB_UP:
                state = s;
                flip = SDL_FLIP_NONE;
                position.velocity.x = 0;
                position.velocity.y = -vx;
                break;
            case UNARMED_CLIMB_DOWN:
            case ARMED_CLIMB_DOWN:
                state = s;
                flip = SDL_FLIP_NONE;
                position.velocity.x = 0;
                position.velocity.y = vx;
                break;
        }
    }
public:
    Swordman(double x, double y, SwordmanState s = SwordmanState::UNARMED_IDLE_FORWARD): Entity(EntityRole::PLAYER) {
        position = {x,y,0,0,0,0};
        state = s;
        flip = SDL_FLIP_NONE;
        setup_controller();
        setup_sprite();
    }
    ~Swordman() {
        if(!loaded) return;
        for(int i=0; i<8;i++) {
            SDL_DestroyTexture(armed_idle[i]);
            SDL_DestroyTexture(armed_walk[i]);
            SDL_DestroyTexture(unarmed_idle[i]);
            SDL_DestroyTexture(unarmed_walk[i]);
        }
        for(int i = 0; i<11; i++) {
            SDL_DestroyTexture(armed_attack[i]);
        }
    }
    void setup_controller() override {
        controller.add_keydown_handler("toggle_sword_mode", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_Q) return false;
            switch(this->state) {
                case ARMED_IDLE_FORWARD:
                    this->set_state(UNARMED_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_IDLE_BACKWARD:
                    this->set_state(UNARMED_IDLE_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_WALK_FORWARD:
                    this->set_state(UNARMED_WALK_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_WALK_BACKWARD:
                    this->set_state(UNARMED_WALK_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_IDLE_FORWARD:
                    this->set_state(UNARMED_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_WALK_FORWARD:
                    this->set_state(UNARMED_WALK_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_IDLE_BACKWARD:
                    this->set_state(UNARMED_IDLE_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_WALK_BACKWARD:
                    this->set_state(UNARMED_WALK_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case UNARMED_IDLE_FORWARD:
                    this->set_state(ARMED_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case UNARMED_IDLE_BACKWARD:
                    this->set_state(ARMED_IDLE_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case UNARMED_WALK_FORWARD:
                    this->set_state(ARMED_WALK_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case UNARMED_WALK_BACKWARD:
                    this->set_state(ARMED_WALK_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case UNARMED_CLIMB_UP:
                    this->set_state(UNARMED_CLIMB_UP);
                    this->sprite_ticker = 0;
                    return true;
                case UNARMED_CLIMB_DOWN:
                    this->set_state(ARMED_CLIMB_DOWN);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_CLIMB_UP:
                    this->set_state(UNARMED_CLIMB_UP);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_CLIMB_DOWN:
                    this->set_state(UNARMED_CLIMB_DOWN);
                    this->sprite_ticker = 0;
                    return true;
            }
        });
        controller.add_keydown_handler("attack_keydown", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_SPACE) return false;
            // only attack when in armed state
            switch(this->state) {
                case ARMED_IDLE_FORWARD:
                    this->set_state(ARMED_ATTACK_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_IDLE_BACKWARD:
                    this->set_state(ARMED_ATTACK_IDLE_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_WALK_FORWARD:
                    this->set_state(ARMED_ATTACK_WALK_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_WALK_BACKWARD:
                    this->set_state(ARMED_ATTACK_WALK_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                default:
                    return false;
            }
        });
        controller.add_keyup_handler("attack_keyup", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_SPACE) return false;
            switch(this->state) {
                case ARMED_ATTACK_IDLE_FORWARD:
                    this->set_state(ARMED_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_IDLE_BACKWARD:
                    this->set_state(ARMED_IDLE_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_WALK_FORWARD:
                    this->set_state(ARMED_WALK_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_WALK_BACKWARD:
                    this->set_state(ARMED_WALK_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                default:
                    return false;
            }
        });

        controller.add_keydown_handler("forward_arrow_keydown", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_D) return false;
            switch(this->state) {
                case UNARMED_CLIMB_UP:
                case UNARMED_CLIMB_DOWN:
                case UNARMED_IDLE_FORWARD:
                case UNARMED_IDLE_BACKWARD:
                    this->set_state(UNARMED_WALK_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_CLIMB_UP:
                case ARMED_CLIMB_DOWN:
                case ARMED_IDLE_FORWARD:
                case ARMED_IDLE_BACKWARD:
                    this->set_state(ARMED_WALK_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_IDLE_BACKWARD:
                case ARMED_ATTACK_IDLE_FORWARD:
                    this->set_state(ARMED_ATTACK_WALK_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                default:
                    return false;
            }
        });
        controller.add_keyup_handler("forward_arrow_keyup", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_D) return false;
            switch(this->state) {
                case ARMED_WALK_FORWARD:
                    this->set_state(ARMED_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case UNARMED_WALK_FORWARD:
                    this->set_state(UNARMED_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_WALK_FORWARD:
                    this->set_state(ARMED_ATTACK_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                default:
                    return false;
            }
        });
        controller.add_keydown_handler("backward_arrow_keydown", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_A) return false;
            switch(this->state) {
                case UNARMED_CLIMB_UP:
                case UNARMED_CLIMB_DOWN:
                case UNARMED_IDLE_BACKWARD:
                case UNARMED_IDLE_FORWARD:
                    this->set_state(UNARMED_WALK_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_CLIMB_UP:
                case ARMED_CLIMB_DOWN:
                case ARMED_IDLE_BACKWARD:
                case ARMED_IDLE_FORWARD:
                    this->set_state(ARMED_WALK_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_IDLE_FORWARD:
                case ARMED_ATTACK_IDLE_BACKWARD:
                    this->set_state(ARMED_ATTACK_WALK_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                default:
                    return false;
            }
        });
        controller.add_keyup_handler("backward_arrow_keyup", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_A) return false;
            switch(this->state) {
                case ARMED_WALK_BACKWARD:
                    this->set_state(ARMED_IDLE_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case UNARMED_WALK_BACKWARD:
                    this->set_state(UNARMED_IDLE_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_ATTACK_WALK_BACKWARD:
                    this->set_state(ARMED_ATTACK_IDLE_BACKWARD);
                    this->sprite_ticker = 0;
                    return true;
                default:
                    return false;
            }
        });
        controller.add_keydown_handler("climb_up_keydown", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_W) return false;
            switch(this->state) {
                case ARMED_IDLE_FORWARD:
                case ARMED_IDLE_BACKWARD:
                case ARMED_WALK_FORWARD:
                case ARMED_WALK_BACKWARD:
                    this->set_state(ARMED_CLIMB_UP);
                    this->sprite_ticker = 0;
                    return true;
                case UNARMED_IDLE_FORWARD:
                case UNARMED_IDLE_BACKWARD:
                case UNARMED_WALK_FORWARD:
                case UNARMED_WALK_BACKWARD:
                    this->set_state(UNARMED_CLIMB_UP);
                    this->sprite_ticker = 0;
                    return true;
                default:
                    return false;
            }
        });
        controller.add_keyup_handler("climb_up_keyup", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_W) return false;
            switch(this->state) {
                case UNARMED_CLIMB_UP:
                    this->set_state(UNARMED_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_CLIMB_UP:
                    this->set_state(ARMED_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                default:
                    return false;
            }
        });
        controller.add_keydown_handler("climb_down_keydown", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_S) return false;
            switch(this->state) {
                case ARMED_IDLE_FORWARD:
                case ARMED_IDLE_BACKWARD:
                case ARMED_WALK_FORWARD:
                case ARMED_WALK_BACKWARD:
                    this->set_state(ARMED_CLIMB_DOWN);
                    this->sprite_ticker = 0;
                    return true;
                case UNARMED_IDLE_FORWARD:
                case UNARMED_IDLE_BACKWARD:
                case UNARMED_WALK_FORWARD:
                case UNARMED_WALK_BACKWARD:
                    this->set_state(UNARMED_CLIMB_DOWN);
                    this->sprite_ticker = 0;
                    return true;
                default:
                    return false;
            }

        });
        controller.add_keyup_handler("climb_down_keyup", [this] (const SDL_Scancode& sc) {
            if(sc != SDL_SCANCODE_S) return false;
            switch(this->state) {
                case UNARMED_CLIMB_DOWN:
                    this->set_state(UNARMED_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                case ARMED_CLIMB_DOWN:
                    this->set_state(ARMED_IDLE_FORWARD);
                    this->sprite_ticker = 0;
                    return true;
                default:
                    return false;
            }
        });

    };
    
    void setup_sprite() override {
        sprite.add_tick_handler("tick_handler", [this] (const bool&) {
            this->ticker = (this->ticker + 1) % Swordman::PERIOD;
            if(this->ticker != 0) return false;
            switch(this->state) {
                case ARMED_CLIMB_UP:
                case ARMED_CLIMB_DOWN:
                    this->sprite_ticker = (this->sprite_ticker + 1) % 4;
                    break;
                case ARMED_ATTACK_WALK_FORWARD:
                case ARMED_ATTACK_WALK_BACKWARD:
                case ARMED_ATTACK_IDLE_FORWARD:
                case ARMED_ATTACK_IDLE_BACKWARD:
                    this->sprite_ticker = (this->sprite_ticker + 1) % 11;
                default:
                    this->sprite_ticker = (this->sprite_ticker + 1) % 8;
            }
            return true;
        });
        sprite.add_update_handler("update handler", [this] (const bool&) {
            this->dest.x = this->position.coord.x;
            this->dest.y = this->position.coord.y;
            switch(this->state) {
                case ARMED_IDLE_FORWARD:
                case ARMED_IDLE_BACKWARD:
                    this->current = this->armed_idle[this->sprite_ticker];
                    break;
                case ARMED_WALK_FORWARD:
                case ARMED_WALK_BACKWARD:
                    this->current = this->armed_walk[this->sprite_ticker];
                    break;
                case ARMED_ATTACK_IDLE_FORWARD:
                case ARMED_ATTACK_IDLE_BACKWARD:
                case ARMED_ATTACK_WALK_FORWARD:
                case ARMED_ATTACK_WALK_BACKWARD:
                    this->current = this->armed_attack[this->sprite_ticker];
                    break;
                case UNARMED_IDLE_FORWARD:
                case UNARMED_IDLE_BACKWARD:
                    this->current = this->unarmed_idle[this->sprite_ticker];
                    break;
                case UNARMED_WALK_FORWARD:
                case UNARMED_WALK_BACKWARD:
                    this->current = this->unarmed_idle[this->sprite_ticker];
                    break;
                case UNARMED_CLIMB_UP:
                    this->current = this->unarmed_climb[this->sprite_ticker];
                    break;
                case UNARMED_CLIMB_DOWN:
                    this->current = this->unarmed_climb[this->sprite_ticker];
                    break;
                case ARMED_CLIMB_UP:
                    this->current = this->armed_climb[this->sprite_ticker];
                    break;
                case ARMED_CLIMB_DOWN:
                    this->current = this->armed_climb[this->sprite_ticker];
                    break;
            }
            return true;
        });
        
        sprite.add_render_handler("render handler", [this] (SDL_Renderer* gRenderer) {
            this->load_media(gRenderer);
            SDL_RenderCopyEx(gRenderer, this->current, &(this->source), &(this->dest), 0, nullptr, this->flip);
            return true;
        });
    }
    
    void load_media(SDL_Renderer* gRenderer) override {
        if(loaded) return;
        for(int i = 0; i<11; i++) {
            auto path = std::format("/Users/donaldsontan/Projects/mtd215/mtd215/assets/{}/{:02}.png", "armed_attack", i);
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            armed_attack[i] = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
        for(int i = 0; i<8; i++) {
            auto path = std::format("/Users/donaldsontan/Projects/mtd215/mtd215/assets/{}/{:02}.png", "armed_idle", i);
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            armed_idle[i] = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
        for(int i = 0; i<8; i++) {
            auto path = std::format("/Users/donaldsontan/Projects/mtd215/mtd215/assets/{}/{:02}.png", "armed_walk", i);
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            armed_walk[i] = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
        for(int i = 0; i<8; i++) {
            auto path = std::format("/Users/donaldsontan/Projects/mtd215/mtd215/assets/{}/{:02}.png", "unarmed_idle", i);
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            unarmed_idle[i] = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
        for(int i = 0; i<8; i++) {
            auto path = std::format("/Users/donaldsontan/Projects/mtd215/mtd215/assets/{}/{:02}.png", "unarmed_walk", i);
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            unarmed_walk[i] = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
        for(int i = 0; i<4; i++) {
            auto path = std::format("/Users/donaldsontan/Projects/mtd215/mtd215/assets/{}/{:02}.png", "unarmed_climb", i);
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            unarmed_climb[i] = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
        for(int i = 0; i<4; i++) {
            auto path = std::format("/Users/donaldsontan/Projects/mtd215/mtd215/assets/{}/{:02}.png", "armed_climb", i);
            SDL_Surface* s = IMG_Load(path.c_str());
            if(s == nullptr) throw SDL_Cannot_Load_Media(path, SDL_GetError());
            armed_climb[i] = SDL_CreateTextureFromSurface(gRenderer, s);
            SDL_FreeSurface(s);
        }
        loaded = true;
    }

};

const int Swordman::SOURCE_WIDTH = 512, Swordman::SOURCE_HEIGHT = 512;
const int Swordman::DEST_WIDTH = 400, Swordman::DEST_HEIGHT = 400;
const uint32_t Swordman::PERIOD = 10;
const double Swordman::UNIT = 1;

#endif
