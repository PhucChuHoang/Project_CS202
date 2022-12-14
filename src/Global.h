#ifndef GLOBAL_H
#define GLOBAL_H
#include <raylib.h>
#include <vector>
#include "Constants.h"

class Global {
private:
    Global();
    static Global* _global; 
public:
    static void initialize();
    static const Global& get();
    static void deallocate();

    Texture2D playerTexture[4][4];
    Texture2D dogTexture[3][4];
    Texture2D catTexture[2][4];
    Texture2D birdTexture[6];

    Texture2D vehicleTexture[5][2];
    Texture2D rockTexture; 
    Texture2D roadTexture;
    Texture2D waterPonderTexture;
    Texture2D ambulanceTexture;
    Texture2D trafficLightTexture[2];
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
    
    Sound buttonClick;
    Sound backgroundSound;
};

extern Global* _global;

#endif