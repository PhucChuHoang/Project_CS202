#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H
#include "Entity.h"
enum LIGHTSTATE {
    REDLIGHT = 0,
    GREENLIGHT
};
class TrafficLight: public StaticEntity {
public:
    TrafficLight(float x, float y);
    void draw() override;
    bool toggleStateDrawing(int& ellipseTime);
private:
    LIGHTSTATE state = GREENLIGHT;
};


#endif