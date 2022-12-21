#ifndef BIRD_H
#define BIRD_H

#include "Entity.h"

class Bird: public MovingEntity {
private:
    int currentDirection;
    int currentImage;
    Direction direction;
public:
    Bird(float speed, Direction Direction, float y);
    void update(float elapsedTime, TrafficLight* trafficLight = nullptr) override;
    void draw() override;
};

#endif