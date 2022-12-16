#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H
#include "Entity.h"
enum LIGHTSTATE {
    REDLIGHT = 0,
    YELLOWLIGHT,
    GREENLIGHT
};
class TrafficLight: public StaticEntity {
public:
    TrafficLight(float x, float y, int redTime = 2, int yellowTime = 2, int greenTime = 10);

    void draw();

    LIGHTSTATE getLightState();

    void drawAdjustState(int& ellipseTime);
private:
    LIGHTSTATE state = GREENLIGHT;
    int red, yellow, green;
};


#endif