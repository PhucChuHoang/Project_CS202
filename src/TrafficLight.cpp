#include "TrafficLight.h"
#include "Constants.h"
#include "Global.h"

TrafficLight::TrafficLight(float x, float y): StaticEntity(nullptr,Global::get().trafficLightTexture[0], false, x, y) {}
void TrafficLight::draw() {
    DrawTexturePro((state == REDLIGHT) ? Global::get().trafficLightTexture[1]: Global::get().trafficLightTexture[0], {0,0,(float)this->getTexture().width,(float)this->getTexture().height}, {0, 60, 60,120}, {0,0}, -90, WHITE);
}
bool TrafficLight::toggleStateDrawing(int& ellipseTime) {
    if ((state == GREENLIGHT) && ellipseTime == 10)
    {
        ellipseTime = 0;
        state = REDLIGHT;
        this->draw();
        return true;
    } else if ((state == REDLIGHT) && ellipseTime == 2)
    {
        ellipseTime = 0;
        state = GREENLIGHT;
        this->draw();
        return true;
    }
    this->draw();
    return false;
}