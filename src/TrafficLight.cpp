#include "TrafficLight.h"
#include "Constants.h"
#include "Global.h"

TrafficLight::TrafficLight(float x, float y, const Texture& texture): StaticEntity(texture, false, x, y) {}
void TrafficLight::draw() {
    DrawTexturePro(this->getTexture(), {0,0,(float)this->getTexture().width,(float)this->getTexture().height}, {0, 60, 60,120}, {0,0}, -90, WHITE);
}