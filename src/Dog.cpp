#include "Dog.h"
#include "Constants.h"
#include "Global.h"

Dog::Dog(float speed, Direction direction, float y): 
    MovingEntity(Global::get().dogTexture[(speed == 0) ?  2: (direction == DIRECTION_LEFT)? 0: 1 ][0], speed, 0 , y), direction(direction),  currentImage(0) {
    
    // assign later because Entity haven't initilized
    x = (direction==DIRECTION_LEFT? SCREEN_WIDTH : -getWidth());
    currentDirection = (direction==DIRECTION_LEFT)? 0 : (direction==DIRECTION_RIGHT) ? 1: 2;
}

void Dog::update(float elapsedTime) {
    if(direction == DIRECTION_LEFT) {
        x -= elapsedTime * speed;
    } else if(direction == DIRECTION_RIGHT) {
        x += elapsedTime * speed;
    }
}

void Dog::draw() {
    DrawTexture(Global::get().dogTexture[currentDirection][currentImage / 4], int(x + 0.5), int(y + 0.5), WHITE);       
    currentImage++;
    if (currentImage == 16) {       //For draw 4 images
        currentImage = 0;
    }
}