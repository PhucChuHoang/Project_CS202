#include "Bird.h"
#include "Constants.h"
#include "Global.h"

Bird::Bird(float speed, float y): 
    MovingEntity(Global::get().birdTexture[0], speed, 0 , y), currentImage(0) {
    
    // assign later because Entity haven't initilized
    x =  -getWidth();
}

void Bird::update(float elapsedTime) {
    x += elapsedTime * speed;
}

void Bird::draw() {
    DrawTexture(Global::get().birdTexture[currentImage / 6], int(x + 0.5), int(y + 0.5), WHITE);       
    currentImage++;
    if (currentImage == 36) {       //For draw 4 images
        currentImage = 0;
    }
}