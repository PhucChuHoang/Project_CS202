#ifndef BIRD_H
#define BIRD_H

#include "Entity.h"

class Bird: public MovingEntity {
private:
    Direction direction;
    int currentImage;
public:
    Bird(float speed, Direction direction, float y);
    void update(float elapsedTime, TrafficLight* trafficLight = nullptr) override;
    void draw() override;
};

#endif