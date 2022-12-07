#include "MainMenu.h"
#include "Level.h"
using std::cout;
using std::endl;

MainMenu::MainMenu() {  
    background = LoadTexture("img/background.png");
    playButton = LoadTexture("img/button/PlayNormal.png");
    playButtonHover = LoadTexture("img/button/PlayHover.png");
    loadSaveButton = LoadTexture("img/button/LoadSaveNormal.png");
    loadSaveButtonHover = LoadTexture("img/button/LoadSaveHover.png");
    ScoreboardButton = LoadTexture("img/button/ScoreboardNormal.png");
    ScoreboardButtonHover = LoadTexture("img/button/ScoreboardHover.png");
    settingsButton = LoadTexture("img/button/SettingsNormal.png");
    settingsButtonHover = LoadTexture("img/button/SettingsHover.png");
    exitButton = LoadTexture("img/button/QuitNormal.png");
    exitButtonHover = LoadTexture("img/button/QuitHover.png");
    mouseLocation = { 0, 0 };
    playButtonBounds = { (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height), 237, 70};                        //x, y, width = 237, height = 70
    loadSaveButtonBounds = { (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 88, 237, 70};               
    ScoreboardButtonBounds = { (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 176, 237, 70};
    settingsButtonBounds = { (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 264, 237, 70};
    exitButtonBounds = { (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 352, 237, 70};
}

bool MainMenu::showMenu() { // return true if play button is pressed
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    mouseLocation = GetMousePosition();
    if (CheckCollisionPointRec(mouseLocation, playButtonBounds)) {
        DrawTexture(playButtonHover, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height), WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            cout << "Play button pressed" << endl;
            EndDrawing();
            return true;
        }
    }
    else {
        DrawTexture(playButton, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height), WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, loadSaveButtonBounds)) {
        DrawTexture(loadSaveButtonHover, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 88, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            cout << "Load/Save button pressed" << endl;
        }
    }
    else {
        DrawTexture(loadSaveButton, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 88, WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, ScoreboardButtonBounds)) {
        DrawTexture(ScoreboardButtonHover, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 176, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            cout << "Scoreboard button pressed" << endl;
        }
    }
    else {
        DrawTexture(ScoreboardButton, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 176, WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, settingsButtonBounds)) {
        DrawTexture(settingsButtonHover, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 264, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            cout << "Settings button pressed" << endl;
        }
    }
    else {
        DrawTexture(settingsButton, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 264, WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, exitButtonBounds)) {
        DrawTexture(exitButtonHover, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 352, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            cout << "Exit button pressed" << endl;
        }
    }
    else {
        DrawTexture(exitButton, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 352, WHITE);
    }
    EndDrawing();
    return false;
}

MainMenu::~MainMenu() {
    UnloadTexture(background);
    UnloadTexture(playButton);
    UnloadTexture(playButtonHover);
    UnloadTexture(loadSaveButton);
    UnloadTexture(loadSaveButtonHover);
    UnloadTexture(ScoreboardButton);
    UnloadTexture(ScoreboardButtonHover);
    UnloadTexture(settingsButton);
    UnloadTexture(settingsButtonHover);
    UnloadTexture(exitButton);
    UnloadTexture(exitButtonHover);
}