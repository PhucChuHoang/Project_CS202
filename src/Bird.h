#ifndef BIRD_H
#define BIRD_H

#include "Entity.h"

class Bird: public MovingEntity {
private:
    int currentImage;
public:
    Bird(float speed, float y);
    void update(float elapsedTime);
    void draw() override;
};

#endif