#include "Rock.h"
#include "Constants.h"
#include "Global.h"

Rock::Rock(float x, float y): StaticEntity(nullptr,Global::get().rockTexture, false, x, y) {}