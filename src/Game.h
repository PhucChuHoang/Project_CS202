#ifndef GAME_H
#define GAME_H

#include "MainMenu.h"
#include "Level.h"

enum GameState {
    GAME_STATE_MAIN_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_LOADGAME,
    GAME_STATE_SCOREBOARD,
    GAME_STATE_SETTINGS,
    GAME_STATE_EXIT
};

int COUNT_FRAME = 0;
int COUNT_TIME = 0;

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