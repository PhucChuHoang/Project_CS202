#ifndef CLOUDS_H
#define CLOUDS_H
#include "Entity.h"

class Clouds: public MovingEntity {
private:    
    float originalX, startingX;
    Direction startingDirection, curDirection;
public:
    Clouds(float x, float y);
    void reset();
    void update(float elapedTime);
};
#endif