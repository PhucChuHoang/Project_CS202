#include "Global.h"
#include <cassert>

Global* Global::_global = nullptr;

Global::Global() {
    string playerPath = "img/character/";
    for (int i = 0; i < 4; ++i) {
        playerTexture[0][i] = LoadTexture((playerPath + "Front" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[1][i] = LoadTexture((playerPath + "Behind" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[2][i] = LoadTexture((playerPath + "Left" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[3][i] = LoadTexture((playerPath + "Right" + char(i + 1 + '0') + ".png").c_str());
    }
    carTexture = LoadTexture(CAR_IMAGE);
    rockTexture = LoadTexture(ROCK_IMAGE);
    roadTexture = LoadTexture(ROAD_IMAGE);
    waterPonderTexture = LoadTexture(WATER_PONDER_IMAGE);
    ambulanceTexture = LoadTexture(AMBULANCE_IMAGE);
    trafficLightTexture[0] = LoadTexture("img/images/traffic_green.png");
    trafficLightTexture[1] = LoadTexture("img/images/traffic_red.png");
    grassTexture = LoadTexture(GRASS_IMAGE);

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
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                UnloadTexture(_global->playerTexture[i][j]);
            }
        }
        UnloadTexture(_global->carTexture);
        UnloadTexture(_global->rockTexture);
        UnloadTexture(_global->roadTexture);
        UnloadTexture(_global->waterPonderTexture);
        UnloadTexture(_global->ambulanceTexture);
        UnloadTexture(_global->grassTexture);
        for(int i = 0; i < 2; i++) {
            UnloadTexture(_global->trafficLightTexture[i]);
        }
        _global = nullptr;
    }
}