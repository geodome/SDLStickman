#ifndef SWORDMAN_H
#define SWORDMAN_H

#include <string>
#include <iostream>
#include <format>
#include "SDL2/SDL_render.h"
#include "SDL2_image/SDL_image.h"
#include "entity.h"
#include "exceptions.h"

enum SwordmanState {
    ARMED_IDLE_FORWARD,
    ARMED_IDLE_BACKWARD,
    ARMED_WALK_FORWARD,
    ARMED_WALK_BACKWARD,
    ARMED_CLIMB_UP_FORWARD,
    ARMED_CLIMB_UP_BACKWARD,
    ARMED_CLIMB_DOWN_FORWARD,
    ARMED_CLIMB_DOWN_BACKWARD,
    ARMED_ATTACK_IDLE_FORWARD,
    ARMED_ATTACK_IDLE_BACKWARD,
    ARMED_ATTACK_WALK_FORWARD,
    ARMED_ATTACK_WALK_BACKWARD,
    UNARMED_IDLE_FORWARD,
    UNARMED_IDLE_BACKWARD,
    UNARMED_WALK_FORWARD,
    UNARMED_WALK_BACKWARD,
    UNARMED_CLIMB_UP_FORWARD,
    UNARMED_CLIMB_UP_BACKWARD,
    UNARMED_CLIMB_DOWN_FORWARD,
    UNARMED_CLIMB_DOWN_BACKWARD
};

class Swordman: public Entity {
    static const int SOURCE_WIDTH, SOURCE_HEIGHT, DEST_WIDTH, DEST_HEIGHT;
    static const uint32_t PERIOD;
    SDL_Rect source{96,96,320,320}, dest{0,0,Swordman::DEST_WIDTH, Swordman::DEST_HEIGHT};
    SDL_Texture* current;
    SDL_Texture* armed_idle[8];
    SDL_Texture* armed_walk[8];
    SDL_Texture* armed_attack[11];
    SDL_Texture* armed_climb[4];
    SDL_Texture* unarmed_idle[8];
    SDL_Texture* unarmed_walk[8];
    SDL_Texture* unarmed_climb[4];
    uint32_t ticker = 0, sprite_ticker = 0;
    SDL_RendererFlip flip;
    bool loaded = false;
    SwordmanState state;
    
    void set_state(SwordmanState s);
    
public:
    
    Swordman(double x, double y, bool forward = true);
    
    bool on_ladder();
    
    ~Swordman();
    
    void setup_controller() override;

    void setup_sprite() override;
    
    void load_media(SDL_Renderer*) override;

};


#endif
