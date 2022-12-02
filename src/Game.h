#ifndef GAME_H
#define GAME_H

#include "MainMenu.h"
#include "Level.h"

enum GameState {
    GAME_STATE_MAIN_MENU,
    GAME_STATE_PLAYING
};

class Game
{
private:
    GameState state;
    MainMenu* mainMenu;
    Level* level;
public:
    Game();
    void run();
    ~Game();
};

#endif