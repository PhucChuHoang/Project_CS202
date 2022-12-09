#include "SettingsMenu.h"

SettingsMenu::SettingsMenu() {
    background = LoadTexture("img/button/background.png");
    settingsTable = LoadTexture("img/button/settingsTable.png");
    enableSound = LoadTexture("img/button/enableSound.png");
    muteSound = LoadTexture("img/button/muteSound.png");
    adjustButtonLeft = LoadTexture("img/button/adjustButtonLeft.png");
    adjustButtonRight = LoadTexture("img/button/adjustButtonRight.png");
    volumeButton = LoadTexture("img/button/VolumeButton.png");
    returnButton = LoadTexture("img/button/ReturnButton.png");
    muteSoundRect = { (float)SCREEN_WIDTH / 2 - muteSound.width / 2, (float)SCREEN_HEIGHT / 2 + 120, (float)muteSound.width, (float)muteSound.height };
    enableSoundRect = { (float)SCREEN_WIDTH / 2 - enableSound.width / 2, (float)SCREEN_HEIGHT / 2 + 120, (float)enableSound.width, (float)enableSound.height };
    adjustButtonLeftRect = { (float)SCREEN_WIDTH / 2 - 2*adjustButtonLeft.width, (float)SCREEN_HEIGHT / 2, (float)adjustButtonLeft.width, (float)adjustButtonLeft.height };
    adjustButtonRightRect = { (float)SCREEN_WIDTH / 2 + adjustButtonLeft.width, (float)SCREEN_HEIGHT / 2, (float)adjustButtonRight.width, (float)adjustButtonRight.height };
    returnButtonRect = { (float)SCREEN_WIDTH / 2 - returnButton.width / 2, (float)SCREEN_HEIGHT / 2 + 350, (float)returnButton.width, (float)returnButton.height };
    isMute = false;
    currentVolume = 0.6f;
}

SettingsMenu::~SettingsMenu() {
    UnloadTexture(settingsTable);
    UnloadTexture(enableSound);
    UnloadTexture(muteSound);
    UnloadTexture(adjustButtonLeft);
    UnloadTexture(adjustButtonRight);
    UnloadTexture(background);
    UnloadTexture(volumeButton);
    UnloadTexture(returnButton);
}

int SettingsMenu::drawSettings() {
    BeginDrawing();
    ClearBackground(WHITE);
    mouseLocation = GetMousePosition();
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(settingsTable, SCREEN_WIDTH / 2 - settingsTable.width / 2, SCREEN_HEIGHT / 2 - settingsTable.height / 2, WHITE);
    DrawTexture(volumeButton, SCREEN_WIDTH / 2 - volumeButton.width / 2, SCREEN_HEIGHT / 2 - volumeButton.height - 40, WHITE);
    DrawTexture(returnButton, SCREEN_WIDTH / 2 - returnButton.width / 2, SCREEN_HEIGHT / 2 + 350, WHITE);
    if (isMute) {
        DrawTexture(muteSound, SCREEN_WIDTH / 2 - muteSound.width / 2, SCREEN_HEIGHT / 2 + 120, WHITE);
    }
    else {
        DrawTexture(enableSound, SCREEN_WIDTH / 2 - enableSound.width / 2, SCREEN_HEIGHT / 2 + 120, WHITE);
    }
    DrawTexture(adjustButtonLeft, SCREEN_WIDTH / 2 - 2*adjustButtonLeft.width, SCREEN_HEIGHT / 2, WHITE);
    DrawTexture(adjustButtonRight, SCREEN_WIDTH / 2 + adjustButtonLeft.width, SCREEN_HEIGHT / 2, WHITE);
    if (CheckCollisionPointRec(mouseLocation, muteSoundRect) || CheckCollisionPointRec(mouseLocation, enableSoundRect)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isMute = !isMute;
            setMute(isMute);
        }
    }
    else if (CheckCollisionPointRec(mouseLocation, adjustButtonLeftRect)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            setSoundSmaller();
        }
    }
    else if (CheckCollisionPointRec(mouseLocation, adjustButtonRightRect)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            setSoundBigger();
        }
    }
    else if (CheckCollisionPointRec(mouseLocation, returnButtonRect)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 1;
        }
    }
    EndDrawing();
    return 0;
}

void SettingsMenu::setSoundSmaller() {
    if (currentVolume == 0.0f) return;
    SetSoundVolume(Global::get().backgroundSound, currentVolume -= 0.1f);
    SetSoundVolume(Global::get().buttonClick, currentVolume -= 0.1f);
    currentVolume -= 0.1f;
}

void SettingsMenu::setSoundBigger() {
    if (currentVolume == 1.0f) return;
    SetSoundVolume(Global::get().backgroundSound, currentVolume += 0.1f);
    SetSoundVolume(Global::get().buttonClick, currentVolume += 0.1f);
    currentVolume += 0.1f;
}

void SettingsMenu::setMute(bool isMute) {
    if (isMute == true) {
        PauseSound(Global::get().backgroundSound);
        PauseSound(Global::get().buttonClick);
    }
    else {
        ResumeSound(Global::get().backgroundSound);
        ResumeSound(Global::get().buttonClick);
    }
}