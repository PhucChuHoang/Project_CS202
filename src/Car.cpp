#include "Car.h"
#include "Constants.h"
#include "Global.h"

Car::Car(float speed, Direction direction, float y): 
    MovingEntity((direction == DIRECTION_LEFT)? Global::get().vehicleTexture[GetRandomValue(0, 4)][0]: Global::get().vehicleTexture[GetRandomValue(0, 4)][1], speed, 0 , y), direction(direction) {
    
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
