#ifndef GLOBAL_H
#define GLOBAL_H
#include <raylib.h>
#include <vector>
#include "Constants.h"

class Global {
private:
    Global();
    static Global* _global; 
public:
    static void initialize();
    static const Global& get();
    static void deallocate();

    Texture2D playerTexture[4][4];
    Texture2D dogTexture[3][4];
    Texture2D catTexture[2][4];

    Texture2D vehicleTexture[5];
    Texture2D rockTexture; 
    Texture2D roadTexture;
    Texture2D waterPonderTexture;
    Texture2D ambulanceTexture;
    Texture2D trafficLightTexture[2];
    Texture2D grassTexture;
    
    Sound buttonClick;
    Sound backgroundSound;
};

extern Global* _global;

#endif