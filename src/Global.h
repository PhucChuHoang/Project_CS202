#ifndef GLOBAL_H
#define GLOBAL_H
#include <raylib.h>
#include <vector>
#include "Clouds.h"
#include "Constants.h"

using std::vector;
class Global
{
private:
    Global();
    static Global *_global; 
    void genClouds();
public:
    static void initialize();
    static const Global &get();
    static void deallocate();

    Texture2D playerTexture[4][4];
    Texture2D dogTexture[3][4];
    Texture2D catTexture[2][4];
    Texture2D birdTexture[2][6];

    Texture2D vehicleTexture[5][2];
    Texture2D rockTexture;
    Texture2D roadTexture;
    Texture2D waterPonderTexture;
    Texture2D ambulanceTexture;
    Texture2D trafficLightTexture[3];
    Texture2D grassTexture;
    Texture2D coinTexture;

    //Main Menu Textures
    Texture2D background;
    Texture2D gameName;
    Texture2D playButton;
    Texture2D playButtonHover;
    Texture2D loadSaveButton;
    Texture2D loadSaveButtonHover;
    Texture2D ScoreboardButton;
    Texture2D ScoreboardButtonHover;
    Texture2D settingsButton;
    Texture2D settingsButtonHover;
    Texture2D exitButton;
    Texture2D exitButtonHover;

    //Settings menu Textures
    Texture2D settingsTable;
    Texture2D enableSound;
    Texture2D muteSound;
    Texture2D adjustButtonLeft;
    Texture2D adjustButtonRight;
    Texture2D volumeButton;
    Texture2D returnButton;
    Texture2D returnButtonHover;
    Texture2D cloudsTexture[5];

    //Scoreboard menu Textures
    Texture2D scoreboard_title;
    Texture2D scoreboard_player;
    Texture2D scoreboard_level;
    Texture2D scoreboard_time;
    Texture2D scoreboard_board;
    Texture2D scoreboard_inputPanel;

    // all clouds
    vector<Clouds*> allClouds;

    //Loading bar
    Texture2D loadingTable;
    Texture2D loadingBar;
    Rectangle loadingBarRec;

    //Pause Menu
    Texture2D pauseMenu;
    Texture2D resumeButtonHover;
    Texture2D saveButtonHover;
    Texture2D exitPauseButtonHover;

    // Win game Menu
    Texture2D winMenu;
    Texture2D nextStageHover;
    Texture2D saveAndExitHover;
    Texture2D shopHover;

    // Shop 
    Texture2D shopTable;
    Texture2D returnHover;
    Texture2D heartHover;
    Texture2D eyeHover;
    Texture2D speedHover;
    // sounds
    Sound buttonClick;
    Sound backgroundSound;
    Sound carSound;
    Sound birdSound;
    Sound dogSound;
    Sound buyItem;
    Sound coinSound;
    Sound winSound;
    Sound deathSound;
};

extern Global *_global;

#endif