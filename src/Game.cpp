#include "Game.h"
#include "Constants.h"
#include "Global.h"

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
    SetTargetFPS(60);  
    
    Global::initialize();
    state = GAME_STATE_MAIN_MENU;
    mainMenu = new MainMenu();
    level = nullptr;
}

void Game::run() {
    while (!WindowShouldClose())   
    {
        switch (state) {
        case GAME_STATE_MAIN_MENU: {
            if (mainMenu->showMenu()) {
                level = new Level();
                state = GAME_STATE_PLAYING;
            }
            break;
        } 
        case GAME_STATE_PLAYING: {
            if (!level->isOver()) {
                level->update();
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
                level = nullptr;
                state = GAME_STATE_MAIN_MENU;
            }
            break;
        }
        default:
            break;
        }
    }
}

Game::~Game() {
    Global::deallocate();
    if (level != nullptr) {
        delete level;
    }
    delete mainMenu;
    CloseWindow(); 
}