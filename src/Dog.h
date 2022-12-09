#ifndef DOG_H
#define DOG_H

#include "Entity.h"

class Dog: public MovingEntity {
private:
    int currentDirection;
    int currentImage;
    Direction direction;
public:
    Dog(float speed, Direction Direction, float y);
    void update(float elapsedTime);
    void draw() override;
};

#endif