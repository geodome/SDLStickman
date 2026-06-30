#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <memory>
#include "entity.h"

class GameState {
public:
    EntityManager entity_manager;
    GameState() {
        //entity_manager = new EntityManager();
    }
    virtual ~GameState() {
        //delete entity_manager;
    }
};

class GameStateDemo: public GameState {
public:
    GameStateDemo(): GameState() {
        // define and add entities here
        std::cout << "demo created \n";
    }
};

#endif
