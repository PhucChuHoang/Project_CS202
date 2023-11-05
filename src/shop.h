#ifndef SHOP_H
#define SHOP_H
#include <iostream>
#include<raylib.h>
#include"Global.h"

class Shop {
    private:
        Texture2D background;
        Texture2D shopTable;
        Texture2D returnHover;
        Texture2D heartHover;
        Texture2D eyeHover;
        Texture2D speedHover;
        float shopConstHeight;
        float shopConstWidth;
        Vector2 mouseLocation;
        Rectangle heartBound;
        Rectangle eyeBound;
        Rectangle speedBound;
        Rectangle returnBound;

    public:
        Shop();
        ~Shop();
        int shopDraw(int money);
};

#endif