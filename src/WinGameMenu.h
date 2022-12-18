#ifndef WINGAMEMENU_H
#define WINGAMEMENU_H
#include <iostream>
#include<raylib.h>
#include"Global.h"

class WinGameMenu {
    private:
        Texture2D background;
        Texture2D winMenu;
        Texture2D nextStageHover;
        Texture2D saveAndExitHover;
        Texture2D shopHover;
        float winTableConst;
        Vector2 mouseLocation;
        Rectangle nextStageBounds;
        Rectangle saveAndExitBounds;
        Rectangle shopBounds;

    public:
        WinGameMenu();
        ~WinGameMenu();
        int showGameMenu();
};

#endif