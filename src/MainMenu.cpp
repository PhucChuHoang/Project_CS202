#include "MainMenu.h"
using std::cout;
using std::endl;

MainMenu::MainMenu() {  
    background = LoadTexture("img/background.png");
    playButton = LoadTexture("img/playNormal.png");
    playButtonHover = LoadTexture("img/PlayHover.png");
    loadSaveButton = LoadTexture("img/LoadSaveNormal.png");
    loadSaveButtonHover = LoadTexture("img/LoadSaveHover.png");
    settingsButton = LoadTexture("img/SettingsNormal.png");
    settingsButtonHover = LoadTexture("img/SettingsHover.png");
    exitButton = LoadTexture("img/QuitNormal.png");
    exitButtonHover = LoadTexture("img/QuitHover.png");
    mouseLocation = { 0, 0 };
    playButtonBounds = { 566, 270, 233, 70};                        //x, y, width = 233, height = 70
    loadSaveButtonBounds = { 566, 358, 233, 70};                    // 
    settingsButtonBounds = { 566, 446, 233, 70};
    exitButtonBounds = { 566, 534, 233, 70};
}

void MainMenu::drawMenu() {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    mouseLocation = GetMousePosition();
    if (CheckCollisionPointRec(mouseLocation, playButtonBounds)) {
        DrawTexture(playButtonHover, 0, 0, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            cout << "Play button pressed" << endl;
        }
    }
    else {
        DrawTexture(playButton, 0, 0, WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, loadSaveButtonBounds)) {
        DrawTexture(loadSaveButtonHover, 0, 0, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            cout << "Load/Save button pressed" << endl;
        }
    }
    else {
        DrawTexture(loadSaveButton, 0, 0, WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, settingsButtonBounds)) {
        DrawTexture(settingsButtonHover, 0, 0, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            cout << "Settings button pressed" << endl;
        }
    }
    else {
        DrawTexture(settingsButton, 0, 0, WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, exitButtonBounds)) {
        DrawTexture(exitButtonHover, 0, 0, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            cout << "Exit button pressed" << endl;
        }
    }
    else {
        DrawTexture(exitButton, 0, 0, WHITE);
    }
}

MainMenu::~MainMenu() {
    UnloadTexture(background);
    UnloadTexture(playButton);
    UnloadTexture(playButtonHover);
    UnloadTexture(loadSaveButton);
    UnloadTexture(loadSaveButtonHover);
    UnloadTexture(settingsButton);
    UnloadTexture(settingsButtonHover);
    UnloadTexture(exitButton);
    UnloadTexture(exitButtonHover);
}