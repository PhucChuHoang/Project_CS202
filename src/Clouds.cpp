#include "Clouds.h"
#include "Global.h"
#include "Random.h"

Clouds::Clouds(float x, float y): StaticEntity(nullptr,Global::get().cloudsTexture[Random::next(0, 3)], false, x, y) {}