#include "PauseMenu.h"
#include "Game.h"

PauseMenu::PauseMenu() {
    background = Global::get().background;
    pauseMenu = Global::get().pauseMenu;
    resumeButtonHover = Global::get().resumeButtonHover;
    saveButtonHover = Global::get().saveButtonHover;
    exitButtonHover = Global::get().exitPauseButtonHover;

    resumeButtonBounds = { (float)SCREEN_WIDTH / 2 - resumeButtonHover.width / 2, (float)SCREEN_HEIGHT / 2 - resumeButtonHover.height / 2 - resumeButtonHover.height + 15, (float)resumeButtonHover.width, (float)resumeButtonHover.height };
    saveButtonBounds = { (float)SCREEN_WIDTH / 2 - resumeButtonHover.width / 2, (float)SCREEN_HEIGHT / 2 - resumeButtonHover.height / 2 + 73, (float)resumeButtonHover.width, (float)resumeButtonHover.height };
    exitButtonBounds = { (float)SCREEN_WIDTH / 2 - resumeButtonHover.width / 2, (float)SCREEN_HEIGHT / 2 - resumeButtonHover.height / 2 + 207, (float)resumeButtonHover.width, (float)resumeButtonHover.height };
}

PauseMenu::~PauseMenu() {
}

int PauseMenu::showMenu() {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(pauseMenu, (float)SCREEN_WIDTH / 2 - pauseMenu.width / 2, (float)SCREEN_HEIGHT / 2 - pauseMenu.height / 2, WHITE);
    mouseLocation = GetMousePosition();
    if (CheckCollisionPointRec(mouseLocation, resumeButtonBounds)) {
        DrawTexture(resumeButtonHover, (float)SCREEN_WIDTH / 2 - resumeButtonHover.width / 2, (float)SCREEN_HEIGHT / 2 - resumeButtonHover.height / 2 - resumeButtonHover.height + 15, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 1;
        }
    }
    if (CheckCollisionPointRec(mouseLocation, saveButtonBounds)) {
        DrawTexture(saveButtonHover, (float)SCREEN_WIDTH / 2 - resumeButtonHover.width / 2, (float)SCREEN_HEIGHT / 2 - resumeButtonHover.height / 2 + 73, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 2;
        }
    }
    if (CheckCollisionPointRec(mouseLocation, exitButtonBounds)) {
        DrawTexture(exitButtonHover, (float)SCREEN_WIDTH / 2 - resumeButtonHover.width / 2, (float)SCREEN_HEIGHT / 2 - resumeButtonHover.height / 2 + 207, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 3;
        }
    }
    EndDrawing();
    return 0;
}