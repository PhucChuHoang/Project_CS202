#include "Rock.h"
#include "Constants.h"
#include "Global.h"

Rock::Rock(float x, float y): StaticEntity(Global::get().rockTexture, false, x, y) {}