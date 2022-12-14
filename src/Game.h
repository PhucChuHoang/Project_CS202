#ifndef GAME_H
#define GAME_H

#include "MainMenu.h"
#include "SettingsMenu.h"
#include"Scoreboard.h"
#include "Level.h"

enum GameState {
    GAME_STATE_MAIN_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_INPUTNAME,
    GAME_STATE_LOADGAME,
    GAME_STATE_SCOREBOARD,
    GAME_STATE_SETTINGS,
    GAME_STATE_EXIT
};


class Game
{
private:
    GameState state;
    MainMenu* mainMenu;
    SettingsMenu* settingsMenu;
    Scoreboard* scoreboardMenu;
    Level* level;
    int money;
    int numLife;
    int speedLevel;
    int visionLevel;
    int currentLevel;
    float totalTime;
public:
    Game();
    void run();
    void increaseLevel();
    void setLevelIs1();
    int getLevel();
    ~Game();
};

#endif