#include "SaveSlot.h"

SaveSlotMenu::SaveSlotMenu() {
    background = Global::get().background;
    saveSlotTable = Global::get().saveSlotTable;
    returnButton = Global::get().returnButton;
    returnButtonHover = Global::get().returnButtonHover;

    slot1Rect = { (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 133, (float)saveSlotTable.width, 187};
    slot2Rect = { (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 320, (float)saveSlotTable.width, 190 };
    slot3Rect = { (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 510, (float)saveSlotTable.width, 190 };
    returnButtonRect = { (float)(float)SCREEN_WIDTH / 2 - returnButton.width / 2, (float)SCREEN_HEIGHT / 2 + saveSlotTable.height / 2 + returnButton.height / 2 - 20, (float)returnButton.width, (float)returnButton.height };
}

int SaveSlotMenu::drawSaveSlotMenu(int data[][6], float dataTime[]) {
    BeginDrawing();
    mousePos = GetMousePosition();
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(saveSlotTable, SCREEN_WIDTH / 2 - saveSlotTable.width / 2, SCREEN_HEIGHT / 2 - saveSlotTable.height / 2, WHITE);
    if (data[0][0] == 1) {
        DrawText("Slot 1", (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 150, 40, BLACK);
        string level = "Current Level: " + std::to_string(data[0][1]);
        DrawText(level.c_str(), (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 200, 40, BLACK);
        string money = "Money: " + std::to_string(data[0][2]);
        DrawText(money.c_str(), (float)SCREEN_WIDTH / 2 + saveSlotTable.width / 4 - 70, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 200, 40, BLACK);
        string life = "Life: " + std::to_string(data[0][3]);
        DrawText(life.c_str(), (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 250, 40, BLACK);
        DrawText(TextFormat("Times: %.02f", dataTime[0]), (float)SCREEN_WIDTH / 2 + saveSlotTable.width / 4 - 70, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 250, 40, BLACK);
    }
    else {
        DrawText("EMPTY", (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 150, 40, BLACK);
    }
    if (data[1][0] == 1) {
        DrawText("Slot 2", (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 340, 40, BLACK);
        string level = "Current Level: " + std::to_string(data[1][1]);
        DrawText(level.c_str(), (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 390, 40, BLACK);
        string money = "Money: " + std::to_string(data[1][2]);
        DrawText(money.c_str(), (float)SCREEN_WIDTH / 2 + saveSlotTable.width / 4 - 70, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 390, 40, BLACK);
        string life = "Life: " + std::to_string(data[1][3]);
        DrawText(life.c_str(), (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 440, 40, BLACK);
        DrawText(TextFormat("Times: %.02f", dataTime[1]), (float)SCREEN_WIDTH / 2 + saveSlotTable.width / 4 - 70, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 440, 40, BLACK);
    }
    else {
        DrawText("EMPTY", (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 340, 40, BLACK);
    }
    if (data[2][0] == 1) {
        DrawText("Slot 3", (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 530, 40, BLACK);
        string level = "Current Level: " + std::to_string(data[2][1]);
        DrawText(level.c_str(), (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 580, 40, BLACK);
        string money = "Money: " + std::to_string(data[2][2]);
        DrawText(money.c_str(), (float)SCREEN_WIDTH / 2 + saveSlotTable.width / 4 - 70, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 580, 40, BLACK);
        string life = "Life: " + std::to_string(data[2][3]);
        DrawText(life.c_str(), (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 630, 40, BLACK);
        DrawText(TextFormat("Times: %.02f", dataTime[2]), (float)SCREEN_WIDTH / 2 + saveSlotTable.width / 4 - 70, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 630, 40, BLACK);
    }
    else {
        DrawText("EMPTY", (float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2 + 20, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 530, 40, BLACK);
    }
    if (CheckCollisionPointRec(mousePos, returnButtonRect)) {
        DrawTexture(returnButtonHover, (float)SCREEN_WIDTH / 2 - returnButton.width / 2, (float)SCREEN_HEIGHT / 2 + saveSlotTable.height / 2 + returnButton.height / 2 - 20, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 4;
        }
    }
    else {
        DrawTexture(returnButton, (float)SCREEN_WIDTH / 2 - returnButton.width / 2, (float)SCREEN_HEIGHT / 2 + saveSlotTable.height / 2 + returnButton.height / 2 - 20, WHITE);
    }
    DrawLineEx( {(float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 320}, { (float)SCREEN_WIDTH / 2 + saveSlotTable.width / 2, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 320}, 4, BLACK);
    DrawLineEx( {(float)SCREEN_WIDTH / 2 - saveSlotTable.width / 2, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 510}, { (float)SCREEN_WIDTH / 2 + saveSlotTable.width / 2, (float)SCREEN_HEIGHT / 2 - saveSlotTable.height / 2 + 510}, 4, BLACK);
    if (CheckCollisionPointRec(mousePos, slot1Rect)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            EndDrawing();
            return 1;
        }
    }
    if (CheckCollisionPointRec(mousePos, slot2Rect)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            EndDrawing();
            return 2;
        }
    }
    if (CheckCollisionPointRec(mousePos, slot3Rect)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            EndDrawing();
            return 3;
        }
    }
    EndDrawing();
    return 0;
}