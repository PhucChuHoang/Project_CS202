#ifndef GLOBAL_H
#define GLOBAL_H
#include <raylib.h>
#include "Constants.h"

class Global {
private:
    Global();
    static Global* _global; 
public:
    static void initialize();
    static const Global& get();
    static void deallocate();

    const Texture2D playerTexture;
    const Texture2D carTexture;
    const Texture2D rockTexture; 
    const Texture2D roadTexture;
};

extern Global* _global;

#endif