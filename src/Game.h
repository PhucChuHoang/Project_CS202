#ifndef GAME_H
#define GAME_H

#include "MainMenu.h"
#include "SettingsMenu.h"
#include "Scoreboard.h"
#include "PauseMenu.h"
#include "WinGameMenu.h"
#include "Level.h"
#include "shop.h"
#include "SaveSlot.h"
#include <fstream>

enum GameState {
    GAME_STATE_MAIN_MENU,
    GAME_STATE_PLAYING,
    GAME_STATE_INPUTNAME,
    GAME_STATE_LOADGAME,
    GAME_STATE_SCOREBOARD,
    GAME_STATE_SETTINGS,
    GAME_STATE_EXIT,
    GAME_STATE_WON,
    GAME_STATE_SHOP,
    GAME_STATE_CHOOSE_SAVE_SLOT
};


class Game
{
private:
    GameState state;
    MainMenu* mainMenu;
    SettingsMenu* settingsMenu;
    Scoreboard* scoreboardMenu;
    PauseMenu* pauseMenu;
    WinGameMenu *winGameMenu;
    Shop* shop;
    Level* level;
    SaveSlotMenu* saveSlotMenu;
    int data[3][6];
    float dataTime[3];
    int money;
    int numLife;
    int speedLevel;
    int visionLevel;
    int currentLevel;
    float totalTime;
    bool isPause;
public:
    Game();
    void run();
    void increaseLevel();
    void setLevelIs1();
    int getLevel();
    ~Game();
    void save(int slotIndex);
    void load();
};

#endif