#include "Game.h"
#include "Constants.h"

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
    SetTargetFPS(60);  
    mainMenu = new MainMenu();
}

void Game::run() {
    while (!WindowShouldClose())   
    {
        BeginDrawing();
        mainMenu->drawMenu();
        EndDrawing();
    }
}

Game::~Game() {
    delete mainMenu;
    CloseWindow(); 
}