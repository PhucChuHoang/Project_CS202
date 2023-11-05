#include"WaterPond.h"
#include "Constants.h"
#include "Global.h"

WaterPond::WaterPond(float x, float y): StaticEntity(nullptr,Global::get().waterPonderTexture, false, x, y) {}