#include "Bird.h"
#include "Constants.h"
#include "Global.h"

Bird::Bird(float speed, Direction direction, float y): 
    MovingEntity(&(Global::get().birdSound),Global::get().birdTexture[(speed == 0) ?  2: (direction == DIRECTION_LEFT)? 0: 1 ][0], speed, 0 , y), direction(direction),  currentImage(0) {
    
    // assign later because Entity haven't initilized
    x = (direction==DIRECTION_LEFT? SCREEN_WIDTH : -getWidth());
    currentDirection = (direction==DIRECTION_LEFT)? 1 : (direction==DIRECTION_RIGHT) ? 0: 2;
}

void Bird::update(float elapsedTime, TrafficLight* trafficLight) {
    MovingEntity::update(elapsedTime);
    if(direction == DIRECTION_LEFT) {
        x -= elapsedTime * speed;
    } else if(direction == DIRECTION_RIGHT) {
        x += elapsedTime * speed;
    }
}

void Bird::draw() {
    DrawTexture(Global::get().birdTexture[currentDirection][currentImage / 6], int(x + 0.5), int(y + 0.5), WHITE);       
    currentImage++;
    if (currentImage == 24) {       //For draw 4 images
        currentImage = 0;
    }
}