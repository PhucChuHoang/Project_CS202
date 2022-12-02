#include "Car.h"
#include "Constants.h"

Car::Car(float speed, Direction direction, float x, float y): 
    MovingEntity(CAR_IMAGE, speed, x, y), direction(direction) {}

void Car::update(float elapsedTime) {
    if (direction == DIRECTION_LEFT) {
        x -= speed * elapsedTime;
    } else {
        x += speed * elapsedTime;
    }
}

