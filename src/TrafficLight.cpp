#include "TrafficLight.h"
#include "Constants.h"
#include "Global.h"

TrafficLight::TrafficLight(float x, float y, int redTime, int yellowTime, int greenTime): 
                    StaticEntity(nullptr,Global::get().trafficLightTexture[0], false, x, y), 
                    red(redTime), green(greenTime), yellow(yellowTime) {

}

void TrafficLight::draw() {
    DrawTexturePro((state == REDLIGHT) ? Global::get().trafficLightTexture[1]: 
                            (state == GREENLIGHT) ? Global::get().trafficLightTexture[0] : Global::get().trafficLightTexture[2], 
                                    {0,0,(float)this->getTexture().width,(float)this->getTexture().height}, {0, 60, 60,120}, {0,0}, -90, WHITE);
}

void TrafficLight::drawAdjustState(int& ellipseTime) {
    if ((state == GREENLIGHT) && ellipseTime == green)
    {
        ellipseTime = 0;
        state = YELLOWLIGHT;
    } else if (state == YELLOWLIGHT && ellipseTime == yellow) {
        ellipseTime = 0;
        state = REDLIGHT;
    } else if ((state == REDLIGHT) && ellipseTime == red) {
        ellipseTime = 0;
        state = GREENLIGHT;
    }
    this->draw();
}

LIGHTSTATE TrafficLight::getLightState() {
    return state;
}
