#include "Game.h"
#include "Constants.h"
#include "Global.h"

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
    InitAudioDevice();
    SetTargetFPS(60);  
    
    Global::initialize();
    state = GAME_STATE_MAIN_MENU;
    mainMenu = new MainMenu();
    settingsMenu = new SettingsMenu();
    money = 0;
    numLife = 3;
    speedLevel = 0;
    visionLevel = 0;
    currentLevel = 1;
    totalTime = 0;
    level = nullptr;
}

void Game::run() {
    PlaySound(Global::get().backgroundSound);
    while (!WindowShouldClose())   
    {
        switch (state) {
        case GAME_STATE_MAIN_MENU: {
            if (mainMenu->showMenu() == 1) {
                level = new Level(currentLevel);
                state = GAME_STATE_PLAYING;
            }
            else if (mainMenu->showMenu() == 2) {
                state = GAME_STATE_LOADGAME;
            }
            else if (mainMenu->showMenu() == 3) {
                state = GAME_STATE_SCOREBOARD;
            }
            else if (mainMenu->showMenu() == 4) {
                state = GAME_STATE_SETTINGS;
            }
            else if (mainMenu->showMenu() == 5) {
                state = GAME_STATE_EXIT;
            }
            break;
        } 
        case GAME_STATE_PLAYING: {
            if (!level->isOver()) {
                if (level->isWon()) {
                    totalTime += level->getPlayedTime();
                    delete level;
                    level = nullptr;
                    currentLevel++;
                    PlaySound(Global::get().winSound);
                    level = new Level(currentLevel);
                }
                level->update(money);
                if (IsKeyDown(KEY_DOWN)) {
                    level->playerMoveDown();
                }
                if (IsKeyDown(KEY_UP)) {
                    level->playerMoveUp();
                }
                if (IsKeyDown(KEY_RIGHT)) {
                    level->playerMoveRight();
                }
                if (IsKeyDown(KEY_LEFT)) {
                    level->playerMoveLeft();
                }
                level->draw();
            } else {
                delete level;
                currentLevel = 1;
                level = nullptr;
                state = GAME_STATE_MAIN_MENU;
            }
            break;
        }
        case GAME_STATE_LOADGAME: {
            break;
        }
        case GAME_STATE_SCOREBOARD: {
            break;
        }
        case GAME_STATE_SETTINGS: {
            if (settingsMenu->drawSettings() == 1) {
                state = GAME_STATE_MAIN_MENU;
            }
            break;
        }
        case GAME_STATE_EXIT: {
            CloseWindow();
            break;
        }
        default:
            break;
        }
    }
}
void Game::increaseLevel()
{
    currentLevel++;
}
void Game::setLevelIs1()
{
    currentLevel = 1;
}
int Game::getLevel()
{
    return currentLevel;
}
Game::~Game() {
    Global::deallocate();
    if (level != nullptr) {
        delete level;
    }
    delete mainMenu;
    CloseWindow(); 
}