#ifndef MAINMENU_H
#define MAINMENU_H
#include <iostream>
#include <raylib.h>
#include "Global.h"
using std::string;

class MainMenu {
    private:
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
        
        Vector2 mouseLocation;
        Rectangle playButtonBounds;
        Rectangle loadSaveButtonBounds;
        Rectangle ScoreboardButtonBounds;
        Rectangle settingsButtonBounds;
        Rectangle exitButtonBounds;
    public:
        MainMenu();
        ~MainMenu();
        int showMenu();
};

#endif