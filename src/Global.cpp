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
    
    vehicleTexture[0] = LoadTexture("img/images/car_0.png");
    vehicleTexture[1] = LoadTexture("img/images/car_1.png");
    vehicleTexture[2] = LoadTexture("img/images/car_2.png");
    vehicleTexture[3] = LoadTexture("img/images/car_3.png");
    vehicleTexture[4] = LoadTexture("img/images/Ambulance_left.png");

    rockTexture = LoadTexture(ROCK_IMAGE);
    roadTexture = LoadTexture(ROAD_IMAGE);
    waterPonderTexture = LoadTexture(WATER_PONDER_IMAGE);
    trafficLightTexture[0] = LoadTexture("img/images/traffic_green.png");
    trafficLightTexture[1] = LoadTexture("img/images/traffic_red.png");
    grassTexture = LoadTexture(GRASS_IMAGE);

    buttonClick = LoadSound("audio/buttonClick.mp3");
    backgroundSound = LoadSound("audio/background_music.mp3");
    SetSoundVolume(buttonClick, 0.6f);
    SetSoundVolume(backgroundSound, 0.6f);
}

void adjustVolume(float volume) {
    SetSoundVolume(Global::get().buttonClick, volume);
    SetSoundVolume(Global::get().backgroundSound, volume);
    if (volume == 0) {
        PauseSound(Global::get().backgroundSound);
    }
    else {
        ResumeSound(Global::get().backgroundSound);
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
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                UnloadTexture(_global->playerTexture[i][j]);
            }
        }
        
        UnloadTexture(_global->rockTexture);
        UnloadTexture(_global->roadTexture);
        UnloadTexture(_global->waterPonderTexture);
        UnloadTexture(_global->ambulanceTexture);
        UnloadTexture(_global->grassTexture);
        for(int i = 0; i < 2; i++) {
            UnloadTexture(_global->trafficLightTexture[i]);
        }
        UnloadSound(_global->buttonClick);
        UnloadSound(_global->backgroundSound);
        for(int i = 0; i < 5; i++) {
            UnloadTexture(_global->vehicleTexture[i]);
        }
        _global = nullptr;
    }
}