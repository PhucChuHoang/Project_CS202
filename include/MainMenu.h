#include <iostream>
#include "raylib.h"

class MainMenu {
    private:
        Texture2D background;
        Texture2D playButton;
        Texture2D playButtonHover;
        Texture2D loadSaveButton;
        Texture2D loadSaveButtonHover;
        Texture2D settingsButton;
        Texture2D settingsButtonHover;
        Texture2D exitButton;
        Texture2D exitButtonHover;
        Vector2 mouseLocation;
        Rectangle playButtonBounds;
        Rectangle loadSaveButtonBounds;
        Rectangle settingsButtonBounds;
        Rectangle exitButtonBounds;
    public:
        MainMenu();
        ~MainMenu();
        void drawMenu();
};