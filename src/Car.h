#ifndef CAR_H
#define CAR_H

#include "Entity.h"

class Car: public MovingEntity {
private:
    Direction direction;
public:
    Car(float speed, Direction direction, float y);
    void update(float elapsedTime, TrafficLight* trafficLight = nullptr) override;
};

#endif