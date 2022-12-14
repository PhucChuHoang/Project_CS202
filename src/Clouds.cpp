#include"Clouds.h"
#include"Global.h"

Clouds::Clouds(float x, float y): StaticEntity(nullptr,Global::get().cloudsTexture[GetRandomValue(0, 4)], false, x, y) {}