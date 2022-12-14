#include "Coin.h"
#include "Constants.h"
#include "Global.h"

Coin::Coin(float x, float y, int value): StaticEntity(&(Global::get().coinSound),Global::get().coinTexture, false, x, y), value(value) {}

int Coin::getValue() {
    return value;
}