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
    TrafficLight(float x, float y, float redTime = 2.25, float yellowTime = 1.75, float greenTime = 10);

    void draw();

    LIGHTSTATE getLightState();

    void update(float elapsedTime);
    float getYellowTime();
    float getTimer();
private:
    LIGHTSTATE state = GREENLIGHT;
    float red, yellow, green;
    float timer;
};


#endif