#include "SettingsMenu.h"

SettingsMenu::SettingsMenu() {
    settingsTable = Global::get().settingsTable;
    enableSound = Global::get().enableSound;
    muteSound = Global::get().muteSound;
    adjustButtonLeft = Global::get().adjustButtonLeft;
    adjustButtonRight = Global::get().adjustButtonRight;
    background = Global::get().background;
    volumeButton = Global::get().volumeButton;
    returnButton = Global::get().returnButton;
    returnButtonHover = Global::get().returnButtonHover;
    muteSoundRect = { (float)SCREEN_WIDTH / 2 - muteSound.width / 2, (float)SCREEN_HEIGHT / 2 + 120, (float)muteSound.width, (float)muteSound.height };
    enableSoundRect = { (float)SCREEN_WIDTH / 2 - enableSound.width / 2, (float)SCREEN_HEIGHT / 2 + 120, (float)enableSound.width, (float)enableSound.height };
    adjustButtonLeftRect = { (float)SCREEN_WIDTH / 2 - 2*adjustButtonLeft.width, (float)SCREEN_HEIGHT / 2, (float)adjustButtonLeft.width, (float)adjustButtonLeft.height };
    adjustButtonRightRect = { (float)SCREEN_WIDTH / 2 + adjustButtonLeft.width, (float)SCREEN_HEIGHT / 2, (float)adjustButtonRight.width, (float)adjustButtonRight.height };
    returnButtonRect = { (float)SCREEN_WIDTH / 2 - returnButton.width / 2, (float)SCREEN_HEIGHT / 2 + 350, (float)returnButton.width, (float)returnButton.height };
    isMute = false;
    currentVolume = 0.6f;
}

SettingsMenu::~SettingsMenu() {

}

int SettingsMenu::drawSettings() {
    BeginDrawing();
    ClearBackground(WHITE);
    mouseLocation = GetMousePosition();
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(settingsTable, SCREEN_WIDTH / 2 - settingsTable.width / 2, SCREEN_HEIGHT / 2 - settingsTable.height / 2, WHITE);
    DrawTexture(volumeButton, SCREEN_WIDTH / 2 - volumeButton.width / 2, SCREEN_HEIGHT / 2 - volumeButton.height - 40, WHITE);
    if (isMute) {
        DrawTexture(muteSound, SCREEN_WIDTH / 2 - muteSound.width / 2, SCREEN_HEIGHT / 2 + 120, WHITE);
    }
    else {
        DrawTexture(enableSound, SCREEN_WIDTH / 2 - enableSound.width / 2, SCREEN_HEIGHT / 2 + 120, WHITE);
    }
    DrawTexture(adjustButtonLeft, SCREEN_WIDTH / 2 - 2*adjustButtonLeft.width, SCREEN_HEIGHT / 2, WHITE);
    DrawTexture(adjustButtonRight, SCREEN_WIDTH / 2 + adjustButtonLeft.width, SCREEN_HEIGHT / 2, WHITE);
    if (CheckCollisionPointRec(mouseLocation, returnButtonRect)) {
        DrawTexture(returnButtonHover, SCREEN_WIDTH / 2 - returnButton.width / 2, SCREEN_HEIGHT / 2 + 350, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 1;
        }
    }
    else {
        DrawTexture(returnButton, SCREEN_WIDTH / 2 - returnButton.width / 2, SCREEN_HEIGHT / 2 + 350, WHITE);
    }
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
    EndDrawing();
    return 0;
}

void SettingsMenu::setSoundSmaller() {
    if (currentVolume == 0.0f) return;
    SetSoundVolume(Global::get().backgroundSound, currentVolume -= 0.1f);
    SetSoundVolume(Global::get().buttonClick, currentVolume -= 0.1f);
    SetSoundVolume(Global::get().carSound, currentVolume -= 0.1f);
    SetSoundVolume(Global::get().birdSound, currentVolume -= 0.1f);
    SetSoundVolume(Global::get().dogSound, currentVolume -= 0.1f);
    SetSoundVolume(Global::get().buyItem, currentVolume -= 0.1f);
    SetSoundVolume(Global::get().coinSound, currentVolume -= 0.1f);
    SetSoundVolume(Global::get().winSound, currentVolume -= 0.1f);
    SetSoundVolume(Global::get().deathSound, currentVolume -= 0.1f);
    currentVolume -= 0.1f;
}

void SettingsMenu::setSoundBigger() {
    if (currentVolume == 1.0f) return;
    SetSoundVolume(Global::get().backgroundSound, currentVolume += 0.1f);
    SetSoundVolume(Global::get().buttonClick, currentVolume += 0.1f);
    SetSoundVolume(Global::get().carSound, currentVolume += 0.1f);
    SetSoundVolume(Global::get().birdSound, currentVolume += 0.1f);
    SetSoundVolume(Global::get().dogSound, currentVolume += 0.1f);
    SetSoundVolume(Global::get().buyItem, currentVolume += 0.1f);
    SetSoundVolume(Global::get().coinSound, currentVolume += 0.1f);
    SetSoundVolume(Global::get().winSound, currentVolume += 0.1f);
    SetSoundVolume(Global::get().deathSound, currentVolume += 0.1f);
    currentVolume += 0.1f;
}

void SettingsMenu::setMute(bool isMute) {
    if (isMute == true) {
        SetSoundVolume(Global::get().backgroundSound, 0.0f);
        SetSoundVolume(Global::get().buttonClick, 0.0f);
        SetSoundVolume(Global::get().carSound, 0.0f);
        SetSoundVolume(Global::get().birdSound, 0.0f);
        SetSoundVolume(Global::get().dogSound, 0.0f);
        SetSoundVolume(Global::get().buyItem, 0.0f);
        SetSoundVolume(Global::get().coinSound, 0.0f);
        SetSoundVolume(Global::get().winSound, 0.0f);
        SetSoundVolume(Global::get().deathSound, 0.0f);
    }
    else {
        SetSoundVolume(Global::get().backgroundSound, currentVolume);
        SetSoundVolume(Global::get().buttonClick, currentVolume);
        SetSoundVolume(Global::get().carSound, currentVolume);
        SetSoundVolume(Global::get().birdSound, currentVolume);
        SetSoundVolume(Global::get().dogSound, currentVolume);
        SetSoundVolume(Global::get().buyItem, currentVolume);
        SetSoundVolume(Global::get().coinSound, currentVolume);
        SetSoundVolume(Global::get().winSound, currentVolume);
        SetSoundVolume(Global::get().deathSound, currentVolume);
    }
}