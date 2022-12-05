#include "Car.h"
#include "Constants.h"
#include "Global.h"

Car::Car(float speed, Direction direction, float y): 
    MovingEntity(Global::get().carTexture, speed, 0 , y), direction(direction) {
    
    // assign later because Entity haven't initilized
    x = (direction==DIRECTION_LEFT? SCREEN_WIDTH : -getWidth());
}

void Car::update(float elapsedTime) {
    if (direction == DIRECTION_LEFT) {
        x -= speed * elapsedTime;
    } else {
        x += speed * elapsedTime;
    }
}

