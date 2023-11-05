#ifndef COIN_H
#define COIN_H
#include "Entity.h"

class Coin: public StaticEntity {
private:
    int value;
public:
    Coin(float x, float y, int value);
    int getValue();
};


#endif