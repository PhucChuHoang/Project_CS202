#include "WinGameMenu.h"
#include "Game.h"

WinGameMenu::WinGameMenu() {
    background = Global::get().background;
    winMenu = Global::get().winMenu;
    nextStageHover = Global::get().nextStageHover;
    shopHover = Global::get().shopHover;
    saveAndExitHover = Global::get().saveAndExitHover;
    winTableConst = (float) SCREEN_HEIGHT/2 - winMenu.height/2  + 97;

    nextStageBounds = { (float)SCREEN_WIDTH / 2 - nextStageHover.width / 2, winTableConst, (float)nextStageHover.width, (float)nextStageHover.height };
    shopBounds = { (float)SCREEN_WIDTH / 2 - nextStageHover.width / 2, winTableConst  + 23 +  nextStageHover.height, (float)nextStageHover.width, (float)nextStageHover.height };
    saveAndExitBounds = { (float)SCREEN_WIDTH / 2 - nextStageHover.width / 2,winTableConst  + 2*(23 +  nextStageHover.height)+1, (float)nextStageHover.width, (float)nextStageHover.height };
}

WinGameMenu::~WinGameMenu() {
}

int WinGameMenu::showGameMenu() {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(winMenu, (float)SCREEN_WIDTH / 2 - winMenu.width / 2, (float)SCREEN_HEIGHT / 2 - winMenu.height / 2, WHITE);
    mouseLocation = GetMousePosition();
    if (CheckCollisionPointRec(mouseLocation, nextStageBounds)) {
        DrawTexture(nextStageHover, (float)SCREEN_WIDTH / 2 - nextStageHover.width / 2, winTableConst, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 1;
        }
    }
    if (CheckCollisionPointRec(mouseLocation, shopBounds)) {
        DrawTexture(shopHover, (float)SCREEN_WIDTH / 2 - shopHover.width / 2, winTableConst  + 23 +  nextStageHover.height, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 2;
        }
    }
    if (CheckCollisionPointRec(mouseLocation, saveAndExitBounds)) {
        DrawTexture(saveAndExitHover, (float)SCREEN_WIDTH / 2 - saveAndExitHover.width / 2,winTableConst  + 2*(23 +  nextStageHover.height)+1, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 3;
        }
    }
    EndDrawing();
    return 0;
}