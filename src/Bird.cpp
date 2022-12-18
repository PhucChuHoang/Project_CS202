#include "Bird.h"
#include "Constants.h"
#include "Global.h"

Bird::Bird(float speed, Direction direction, float y):
    MovingEntity(&(Global::get().birdSound),Global::get().birdTexture[0], speed, 0 , y), direction(direction), currentImage(0) {
    
    // assign later because Entity haven't initilized
    x = (direction==DIRECTION_LEFT? SCREEN_WIDTH : -getWidth());
}

void Bird::update(float elapsedTime, TrafficLight* trafficLight) {
    MovingEntity::update(elapsedTime);
    if (direction == DIRECTION_LEFT) {
        x -= speed * elapsedTime;
    } else {
        x += speed * elapsedTime;
    }
}

void Bird::draw() {
    DrawTexture(Global::get().birdTexture[currentImage / 6], int(x + 0.5), int(y + 0.5), WHITE);       
    currentImage++;
    if (currentImage == 36) {       //For draw 4 images
        currentImage = 0;
    }
}