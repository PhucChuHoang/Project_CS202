#include "Global.h"
#include <cassert>

Global *Global::_global = nullptr;

Global::Global()
{
    string playerPath = "img/character/";
    string dogPath = "img/images/dogs/";
    string birdPath = "img/images/birds/";
    string cloudsPath = "img/images/clouds/";
    for (int i = 0; i < 4; ++i)
    {
        playerTexture[0][i] = LoadTexture((playerPath + "Front" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[1][i] = LoadTexture((playerPath + "Behind" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[2][i] = LoadTexture((playerPath + "Left" + char(i + 1 + '0') + ".png").c_str());
        playerTexture[3][i] = LoadTexture((playerPath + "Right" + char(i + 1 + '0') + ".png").c_str());
    }

    for (int i = 0; i < 4; ++i)
    {
        dogTexture[0][i] = LoadTexture((dogPath + "dog_left" + char(i + 1 + '0') + ".png").c_str());
        dogTexture[1][i] = LoadTexture((dogPath + "dog_right" + char(i + 1 + '0') + ".png").c_str());
    }
    for (int i = 0; i < 4; ++i)
    {
        dogTexture[2][i] = LoadTexture((dogPath + "dog_standstill" + char(i + 1 + '0') + ".png").c_str());
    }

    for (int i = 0; i < 6; ++i)
    {
        birdTexture[i] = LoadTexture((birdPath + "bird_left" + char(i + 1 + '0') + ".png").c_str());
    }

    for (int i = 0; i < 5; i++)
    {
        vehicleTexture[i][0] = LoadTexture(("img/images/car_" + std::to_string(i) + ".png").c_str());
        vehicleTexture[i][1] = LoadTexture(("img/images/car_" + std::to_string(i) + "_f.png").c_str());
    }

    for (int i = 0; i < 5; i++)
    {
        cloudsTexture[i] = LoadTexture((cloudsPath + "clouds_" + char(i + 1 + '0') + ".png").c_str());
    }

    rockTexture = LoadTexture(ROCK_IMAGE);
    roadTexture = LoadTexture(ROAD_IMAGE);
    waterPonderTexture = LoadTexture(WATER_PONDER_IMAGE);
    trafficLightTexture[0] = LoadTexture("img/images/traffic_green.png");
    trafficLightTexture[1] = LoadTexture("img/images/traffic_red.png");
    grassTexture = LoadTexture(GRASS_IMAGE);
    coinTexture = LoadTexture("img/images/coin.png");

    buttonClick = LoadSound("audio/buttonClick.mp3");
    backgroundSound = LoadSound("audio/background_music.mp3");

    carSound = LoadSound("audio/Car-Crash.mp3");
    birdSound = LoadSound("audio/Bird_2.mp3");

    dogSound = LoadSound("audio/Dog(gau_gau).mp3");

    buyItem = LoadSound("audio/BuyItemSuccessful.mp3");

    coinSound = LoadSound("audio/CoinPickup.mp3");

    winSound = LoadSound("audio/CompleteRound.mp3");

    deathSound = LoadSound("audio/DeathSound.mp3");

    SetSoundVolume(buttonClick, 0.6f);
    SetSoundVolume(backgroundSound, 0.6f);
    SetSoundVolume(carSound, 1.0f);
    SetSoundVolume(birdSound, 2.0f);
    SetSoundVolume(dogSound, 1.0f);
    SetSoundVolume(buyItem, 1.0f);
    SetSoundVolume(coinSound, 0.5f);
    SetSoundVolume(winSound, 1.0f);
    SetSoundVolume(deathSound, 1.0f);
}

void Global::initialize()
{
    if (_global == nullptr)
    {
        _global = new Global();
    }
}

const Global &Global::get()
{
    assert(_global != nullptr);
    return *(_global);
}

void Global::deallocate()
{
    if (_global != nullptr)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                UnloadTexture(_global->playerTexture[i][j]);
            }
        }

        UnloadTexture(_global->rockTexture);
        UnloadTexture(_global->roadTexture);
        UnloadTexture(_global->waterPonderTexture);
        UnloadTexture(_global->ambulanceTexture);
        UnloadTexture(_global->grassTexture);
        for (int i = 0; i < 2; i++)
        {
            UnloadTexture(_global->trafficLightTexture[i]);
        }
        UnloadSound(_global->buttonClick);
        UnloadSound(_global->backgroundSound);
        UnloadSound(_global->carSound);
        UnloadSound(_global->birdSound);
        UnloadSound(_global->dogSound);
        UnloadSound(_global->buyItem);
        UnloadSound(_global->coinSound);
        UnloadSound(_global->winSound);
        UnloadSound(_global->deathSound);
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 2; j++)
                UnloadTexture(_global->vehicleTexture[i][j]);
        }
        _global = nullptr;
    }
}