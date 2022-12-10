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
    playButtonBounds = { (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height), (float)playButton.width, (float)playButton.height};                        //x, y, width = (float)playButton.width, (float)playButton.heightight = 70
    loadSaveButtonBounds = { (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 88, (float)playButton.width, (float)playButton.height};               
    ScoreboardButtonBounds = { (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 176, (float)playButton.width, (float)playButton.height};
    settingsButtonBounds = { (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 264, (float)playButton.width, (float)playButton.height};
    exitButtonBounds = { (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 352, (float)playButton.width, (float)playButton.height};
}

int MainMenu::showMenu() { // 1 = play, 2 = load, 3 = scoreboard, 4 = settings, 5 = exit
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    mouseLocation = GetMousePosition();
    if (CheckCollisionPointRec(mouseLocation, playButtonBounds)) {
        DrawTexture(playButtonHover, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height), WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // EndDrawing(); 
            PlaySound(Global::get().buttonClick);
            return 1;
        }
    }
    else {
        DrawTexture(playButton, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height), WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, loadSaveButtonBounds)) {
        DrawTexture(loadSaveButtonHover, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 88, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // EndDrawing();
            PlaySound(Global::get().buttonClick);
            return 2;
        }
    }
    else {
        DrawTexture(loadSaveButton, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 88, WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, ScoreboardButtonBounds)) {
        DrawTexture(ScoreboardButtonHover, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 176, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // EndDrawing();
            PlaySound(Global::get().buttonClick);
            return 3;
        }
    }
    else {
        DrawTexture(ScoreboardButton, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 176, WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, settingsButtonBounds)) {
        DrawTexture(settingsButtonHover, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 264, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // EndDrawing();
            PlaySound(Global::get().buttonClick);
            return 4;
        }
    }
    else {
        DrawTexture(settingsButton, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 264, WHITE);
    }
    if (CheckCollisionPointRec(mouseLocation, exitButtonBounds)) {
        DrawTexture(exitButtonHover, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 352, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // EndDrawing();
            PlaySound(Global::get().buttonClick);
            return 5;
        }
    }
    else {
        DrawTexture(exitButton, (float)(GetScreenWidth() / 2 - playButton.width / 2), (float)(GetScreenHeight() / 2 - playButton.height) + 352, WHITE);
    }
    EndDrawing();
    return 0;
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