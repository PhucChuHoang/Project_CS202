#include "WinGameMenu.h"
#include "shop.h"

Shop::Shop() {
    background = Global::get().background;
    shopTable = Global::get().shopTable;
    returnHover = Global::get().returnHover;
    heartHover = Global::get().heartHover;
    eyeHover = Global::get().eyeHover;
    speedHover = Global::get().speedHover;
    shopConstHeight = (float) SCREEN_HEIGHT/2 - shopTable.height/2  + 228;
    shopConstWidth = (float) SCREEN_WIDTH/2 - shopTable.width/2 - 2;

    heartBound = { shopConstWidth + 68, shopConstHeight, (float)heartHover.width, (float)heartHover.height };
    eyeBound = { shopConstWidth +  heartHover.width + 150, shopConstHeight, (float)heartHover.width, (float)heartHover.height };
    speedBound = {shopConstWidth + 2*heartHover.width + 238,shopConstHeight, (float)heartHover.width, (float)heartHover.height };
    returnBound = { shopConstWidth + 143, shopConstHeight + 84, (float)returnHover.width, (float)returnHover.height };
}   

Shop::~Shop() {
}

int Shop::shopDraw(int money) {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(shopTable, shopConstWidth+2, shopConstHeight - 228, WHITE);
    DrawText(TextFormat("%i", money), shopConstWidth + 55, shopConstHeight -163, 20, BLACK);
    mouseLocation = GetMousePosition();
    if (CheckCollisionPointRec(mouseLocation, heartBound)) {
        DrawTexture(heartHover, shopConstWidth + 68, shopConstHeight, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 1;
        }
    }
    if (CheckCollisionPointRec(mouseLocation, eyeBound)) {
        DrawTexture(eyeHover, shopConstWidth +  heartHover.width + 150, shopConstHeight, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 2;
        }
    }
    if (CheckCollisionPointRec(mouseLocation, speedBound)) {
        DrawTexture(speedHover, shopConstWidth + 2*heartHover.width + 238,shopConstHeight, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 3;
        }
    }
    if (CheckCollisionPointRec(mouseLocation, returnBound)) {
        DrawTexture(returnHover, shopConstWidth + 143, shopConstHeight + 84, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 4;
        }
    }
    EndDrawing();
    return 0;
}