#include "Global.h"
#include <cassert>

Global* Global::_global = nullptr;

Global::Global(): 
    playerTexture(LoadTexture(PLAYER_IMAGE)),
    carTexture(LoadTexture(CAR_IMAGE)),
    rockTexture(LoadTexture(ROCK_IMAGE)),
    roadTexture(LoadTexture(ROAD_IMAGE)) {}

void Global::initialize() {
    if (_global == nullptr) {
        _global = new Global();
    }
}

const Global& Global::get() {
    assert(_global != nullptr);
    return *(_global);
}

void Global::deallocate() {
    if (_global != nullptr) {
        UnloadTexture(_global->playerTexture);
        UnloadTexture(_global->carTexture);
        UnloadTexture(_global->rockTexture);
        UnloadTexture(_global->roadTexture);
        _global = nullptr;
    }
}