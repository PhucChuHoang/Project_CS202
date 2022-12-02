#ifndef GAME_H
#define GAME_H

#include "MainMenu.h"

class Game
{
private:
    MainMenu* mainMenu;
public:
    Game();
    void run();
    ~Game();
};

#endif