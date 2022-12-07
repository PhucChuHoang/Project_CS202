#include "Global.h"
#include <cassert>

Global* Global::_global = nullptr;

Global::Global(): 
    // playerTexture(LoadTexture(PLAYER_IMAGE)),
    carTexture(LoadTexture(CAR_IMAGE)),
    rockTexture(LoadTexture(ROCK_IMAGE)),
    roadTexture(LoadTexture(ROAD_IMAGE)) {
    playerTexture.resize(4);
    for (int i = 0; i < 4; ++i) {
        playerTexture[i].resize(4);
    }
    string playerPath = "img/character/";
    for (int i = 0; i < 4; ++i) {
        playerTexture[0][i] = LoadTexture((playerPath + "Front" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[1][i] = LoadTexture((playerPath + "Behind" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[2][i] = LoadTexture((playerPath + "Left" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[3][i] = LoadTexture((playerPath + "Right" + char(i + 1 + '0') + ".png").c_str());
    }
}

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
        // UnloadTexture(_global->playerTexture);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                UnloadTexture(_global->playerTexture[i][j]);
            }
        }
        UnloadTexture(_global->carTexture);
        UnloadTexture(_global->rockTexture);
        UnloadTexture(_global->roadTexture);
        _global = nullptr;
    }
}