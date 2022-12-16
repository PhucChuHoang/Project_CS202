#include "TrafficLight.h"
#include "Constants.h"
#include "Global.h"

TrafficLight::TrafficLight(float x, float y, float redTime, float yellowTime, float greenTime): 
                    StaticEntity(nullptr,Global::get().trafficLightTexture[0], false, x, y), 
                    red(redTime), green(greenTime), yellow(yellowTime) {

}

void TrafficLight::draw() {
    DrawTexturePro((state == REDLIGHT) ? Global::get().trafficLightTexture[1]: 
                            (state == GREENLIGHT) ? Global::get().trafficLightTexture[0] : Global::get().trafficLightTexture[2], 
                                    {0,0,(float)this->getTexture().width,(float)this->getTexture().height}, {0, 60, 60,120}, {0,0}, -90, WHITE);
}

void TrafficLight::update(float elapsedTime) {
    timer += elapsedTime;
    while (true) {
        bool ok = true;
        if ((state == GREENLIGHT) && timer >= green) {
            timer -= green;
            state = YELLOWLIGHT;
            ok = false;
        }
        if (state == YELLOWLIGHT && timer >= yellow) {
            timer -= yellow;
            state = REDLIGHT;
            ok = false;
        } else if ((state == REDLIGHT) && timer >= red) {
            timer -= red;
            state = GREENLIGHT;
            ok = false;
        }
        if (ok) {
            break;
        }
    }
}

LIGHTSTATE TrafficLight::getLightState() {
    return state;
}

float TrafficLight::getYellowTime() {
    return yellow;
}

float TrafficLight::getTimer() {
    return timer;
}
