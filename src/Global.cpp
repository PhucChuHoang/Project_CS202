#include "Global.h"
#include "Random.h"
#include <cassert>
#include <algorithm>

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

    for (int i = 0; i < 4; i++)
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

    //Load Main Menu Textures
    background = LoadTexture("img/button/background.png");
    gameName = LoadTexture("img/button/gameName.png");
    playButton = LoadTexture("img/button/PlayNormal.png");
    playButtonHover = LoadTexture("img/button/PlayHover.png");
    loadSaveButton = LoadTexture("img/button/LoadSaveNormal.png");
    loadSaveButtonHover = LoadTexture("img/button/LoadSaveHover.png");
    ScoreboardButton = LoadTexture("img/button/ScoreboardNormal.png");
    ScoreboardButtonHover = LoadTexture("img/button/ScoreboardHover.png");
    settingsButton = LoadTexture("img/button/SettingsNormal.png");
    settingsButtonHover = LoadTexture("img/button/SettingsHover.png");
    exitButton = LoadTexture("img/button/QuitNormal.png");
    exitButtonHover = LoadTexture("img/button/QuitHover.png");

    //Settings menu Textures
    settingsTable = LoadTexture("img/button/settingsTable.png");
    enableSound = LoadTexture("img/button/enableSound.png");
    muteSound = LoadTexture("img/button/muteSound.png");
    adjustButtonLeft = LoadTexture("img/button/adjustButtonLeft.png");
    adjustButtonRight = LoadTexture("img/button/adjustButtonRight.png");
    volumeButton = LoadTexture("img/button/VolumeButton.png");
    returnButton = LoadTexture("img/button/ReturnButton.png");
    returnButtonHover = LoadTexture("img/button/ReturnButtonHover.png");

    // Scoreboard menu Textures
    scoreboard_title = LoadTexture("img/scoreboard/title.png");
    scoreboard_player = LoadTexture("img/scoreboard/player.png");
    scoreboard_level = LoadTexture("img/scoreboard/level.png");
    scoreboard_time = LoadTexture("img/scoreboard/time.png");
    scoreboard_board = LoadTexture("img/scoreboard/scoreboard.png");
    scoreboard_inputPanel = LoadTexture("img/scoreboard/inputpanel.png");

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
    SetSoundVolume(carSound, 2.0f);
    SetSoundVolume(birdSound, 20.0f);
    SetSoundVolume(dogSound, 3.0f);
    SetSoundVolume(buyItem, 1.0f);
    SetSoundVolume(coinSound, 0.3f);
    SetSoundVolume(winSound, 1.0f);
    SetSoundVolume(deathSound, 1.0f);
}

void Global::genClouds() {
    // gen clouds
    Random::setSeed(RANDOM_SEED); // ensure clouds are same for all time
    for (int y = -32; y < SCREEN_HEIGHT; y += 8) {
        int x = Random::next(-256, 0);
        while (x < SCREEN_WIDTH + 64) {
            allClouds.push_back(new Clouds(x, y + Random::next(-4, 4)));
            //x += allClouds.back()->getWidth();
            x += Random::wnext(0, 32, 48);
        }
    }
}

void Global::initialize()
{
    if (_global == nullptr)
    {
        _global = new Global();
        _global->genClouds();
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
        for (int i = 0; i < 4; i++)
        {
            UnloadTexture(_global->cloudsTexture[i]);
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
        UnloadTexture(_global->background);
        UnloadTexture(_global->gameName);
        UnloadTexture(_global->playButton);
        UnloadTexture(_global->playButtonHover);
        UnloadTexture(_global->loadSaveButton);
        UnloadTexture(_global->loadSaveButtonHover);
        UnloadTexture(_global->ScoreboardButton);
        UnloadTexture(_global->ScoreboardButtonHover);
        UnloadTexture(_global->settingsButton);
        UnloadTexture(_global->settingsButtonHover);
        UnloadTexture(_global->exitButton);
        UnloadTexture(_global->exitButtonHover);

        UnloadTexture(_global->settingsTable);
        UnloadTexture(_global->enableSound);
        UnloadTexture(_global->muteSound);
        UnloadTexture(_global->adjustButtonLeft);
        UnloadTexture(_global->adjustButtonRight);
        UnloadTexture(_global->volumeButton);
        UnloadTexture(_global->returnButton);
        UnloadTexture(_global->returnButtonHover);
        _global = nullptr;
    }
}