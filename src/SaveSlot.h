#ifndef SAVESLOT_H
#define SAVESLOT_H
#include "Global.h"

class SaveSlotMenu {
    private:
        Texture2D background;
        Texture2D saveSlotTable;

        Rectangle slot1Rect;
        Rectangle slot2Rect;
        Rectangle slot3Rect;

        Vector2 mousePos;

    public:
        SaveSlotMenu();
        ~SaveSlotMenu();
        int drawSaveSlotMenu(int data[][6], float dataTime[]);
};

#endif