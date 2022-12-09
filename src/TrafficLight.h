#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H
#include "Entity.h"

class TrafficLight: public StaticEntity {
public:
    TrafficLight(float x, float y, const Texture& texture);
    void draw() override;
};


#endif