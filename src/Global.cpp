#include "Global.h"
#include <cassert>

Global* Global::_global = nullptr;

Global::Global() {
    string playerPath = "img/character/";
    string dogPath = "img/images/dogs/";
    string birdPath = "img/images/birds/";
    for (int i = 0; i < 4; ++i) {
        playerTexture[0][i] = LoadTexture((playerPath + "Front" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[1][i] = LoadTexture((playerPath + "Behind" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[2][i] = LoadTexture((playerPath + "Left" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[3][i] = LoadTexture((playerPath + "Right" + char(i + 1 + '0') + ".png").c_str());
    }
    
    for (int i = 0; i < 4; ++i) {
        dogTexture[0][i] = LoadTexture((dogPath + "dog_left" + char(i + 1 + '0') + ".png").c_str());
        dogTexture[1][i] = LoadTexture((dogPath + "dog_right" + char(i + 1 + '0') + ".png").c_str());
    }
    for (int i = 0; i < 4; ++i) {
        dogTexture[2][i] = LoadTexture((dogPath + "dog_standstill" + char(i + 1 + '0') + ".png").c_str());
    }

    for (int i = 0; i < 6; ++i) {
        birdTexture[i] = LoadTexture((birdPath + "bird_left" + char(i + 1 + '0') + ".png").c_str());
    }

    vehicleTexture[0][0] = LoadTexture("img/images/car_0.png");
    vehicleTexture[0][1] = LoadTexture("img/images/car_0_f.png");
    vehicleTexture[1][0] = LoadTexture("img/images/car_1.png");
    vehicleTexture[1][1] = LoadTexture("img/images/car_1_f.png");
    vehicleTexture[2][0] = LoadTexture("img/images/car_2.png");
    vehicleTexture[2][1] = LoadTexture("img/images/car_2_f.png");
    vehicleTexture[3][0] = LoadTexture("img/images/car_3.png");
    vehicleTexture[3][1] = LoadTexture("img/images/car_3_f.png");
    vehicleTexture[4][0] = LoadTexture("img/images/ambulance_0.png");
    vehicleTexture[4][1] = LoadTexture("img/images/ambulance_0_f.png");

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
            for(int j = 0; j < 2; j++) UnloadTexture(_global->vehicleTexture[i][j]);
        }
        _global = nullptr;
    }
}