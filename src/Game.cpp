#include "Game.h"
#include "Constants.h"
#include "Global.h"

#define clearDummyFrame(); BeginDrawing(); EndDrawing();

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
    InitAudioDevice();
    SetTargetFPS(60);  
    
    Global::initialize();
    state = GAME_STATE_MAIN_MENU;
    mainMenu = new MainMenu();
    settingsMenu = new SettingsMenu();
    scoreboardMenu = new Scoreboard();
    money = 0;
    numLife = 3;
    speedLevel = 0;
    visionLevel = 0;
    currentLevel = 1;
    totalTime = 0;
    level = nullptr;
    isPause = false;
}

#include <iostream>

void Game::run() {
    PlaySound(Global::get().backgroundSound);
    while (!WindowShouldClose())   
    {
        switch (state) {
        case GAME_STATE_MAIN_MENU: {
            int currentState = mainMenu->showMenu();
            if (currentState == 1) {
                level = new Level(currentLevel);
                state = GAME_STATE_PLAYING;
                clearDummyFrame();
            }
            else if (currentState == 2) {
                state = GAME_STATE_LOADGAME;
                clearDummyFrame();
            }
            else if (currentState == 3) {
                state = GAME_STATE_SCOREBOARD;
                clearDummyFrame();
            }
            else if (currentState == 4) {
                state = GAME_STATE_SETTINGS;
                clearDummyFrame();
            }
            else if (currentState == 5) {
                state = GAME_STATE_EXIT;
                clearDummyFrame();
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
                level->update(money, isPause);
                level->draw();
                if (IsKeyPressed(KEY_P)) {
                    isPause = !isPause;
                    break;
                }
                if (isPause) {
                    break;
                }
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
            } else {
                state = GAME_STATE_INPUTNAME;
            }
            break;
        }
        case GAME_STATE_INPUTNAME: {
            string name;
            if(scoreboardMenu->renderNameInputPanel(name) == 1) {
                Package new_record("John", currentLevel, totalTime + level->getPlayedTime());
                scoreboardMenu->updateRanking(new_record);
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
            // Initialize score
            if (scoreboardMenu->drawScoreboard() == 1) {
                state = GAME_STATE_MAIN_MENU;

                clearDummyFrame();
            }
            break;
        }
        case GAME_STATE_SETTINGS: {
            if (settingsMenu->drawSettings() == 1) {
                state = GAME_STATE_MAIN_MENU;

                clearDummyFrame();
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