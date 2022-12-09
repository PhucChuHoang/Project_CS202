#include"WaterPond.h"
#include "Constants.h"
#include "Global.h"

WaterPond::WaterPond(float x, float y): StaticEntity(Global::get().waterPonderTexture, false, x, y) {}