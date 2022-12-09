#pragma once
#include <iostream>
#include <raylib.h>
#include "Global.h"
using std::string;

class SettingsMenu {
    private:
        Texture2D settingsTable;
        Texture2D enableSound;
        Texture2D muteSound;
        Texture2D adjustButtonLeft;
        Texture2D adjustButtonRight;
        Texture2D background;
        Texture2D volumeButton;
        Texture2D returnButton;

        Vector2 mouseLocation;

        Rectangle muteSoundRect;
        Rectangle enableSoundRect;
        Rectangle adjustButtonLeftRect;
        Rectangle adjustButtonRightRect;
        Rectangle returnButtonRect;
        bool isMute;
        float currentVolume;
    public:
        SettingsMenu();
        ~SettingsMenu();
        int drawSettings();
        void setSoundSmaller();
        void setSoundBigger();
        void setMute(bool mute);
};