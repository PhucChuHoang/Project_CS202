#include "Player.h"
#include "Constants.h"
#include "Global.h"

Player::Player(float speed): MovingEntity(Global::get().playerTexture[0][0], speed), 
    currentDirection(0), currentImage(0), flagMovement(false) {}

void Player::moveUp() {
    currentDirection = 1;
    flagMovement = true;
    y -= speed * elapsedTime;
}
void Player::moveDown() {
    currentDirection = 0;
    flagMovement = true;
    y += speed * elapsedTime;
}
void Player::moveLeft() {
    currentDirection = 2;
    flagMovement = true;
    x -= speed * elapsedTime;
}
void Player::moveRight() {
    currentDirection = 3;
    flagMovement = true;
    x += speed * elapsedTime;
}

void Player::update(float elapsedTime) {
    this->elapsedTime = elapsedTime;
}

void Player::draw() {                      //0 = up, 1 = down, 2 = left, 3 = right
    DrawTexture(Global::get().playerTexture[currentDirection][currentImage / 4], int(x + 0.5), int(y + 0.5), WHITE);       
    if (flagMovement) {
        currentImage++;
        if (currentImage == 16) {       //For draw 4 images
            currentImage = 0;
            flagMovement = false;
        }
    }
}