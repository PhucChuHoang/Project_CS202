#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include <iostream>
#include <raylib.h>
#include "Global.h"

class PauseMenu {
    private:
        Texture2D background;
        Texture2D pauseMenu;
        Texture2D resumeButtonHover;
        Texture2D saveButtonHover;
        Texture2D exitButtonHover;

        Vector2 mouseLocation;
        Rectangle resumeButtonBounds;
        Rectangle saveButtonBounds;
        Rectangle exitButtonBounds;

    public:
        PauseMenu();
        ~PauseMenu();
        int showMenu();
};

#endif