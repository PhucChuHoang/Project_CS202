#include "Player.h"
#include "Constants.h"
#include "Global.h"
#include <algorithm>

const Texture DUMMY_PLAYER_TEXTURE = {0, 30, 30, 0, 0};

Player::Player(float speed): MovingEntity(nullptr,DUMMY_PLAYER_TEXTURE, speed, (SCREEN_WIDTH + DUMMY_PLAYER_TEXTURE.width) / 2, SCREEN_HEIGHT - 60), 
    currentDirection(0), currentImage(0), flagMovement(false) {}

void Player::moveUp(bool updateDirection) {
    if (updateDirection) {
        currentDirection = 1;
        flagMovement = true;
    }
    y -= speed * elapsedTime;
}
void Player::moveDown(bool updateDirection) {
    if (updateDirection) {
        currentDirection = 0;
        flagMovement = true;
    }
    y += speed * elapsedTime;
}
void Player::moveLeft(bool updateDirection) {
    if (updateDirection) {
        currentDirection = 2;
        flagMovement = true;
    }
    x -= speed * elapsedTime;
}
void Player::moveRight(bool updateDirection) {
    if (updateDirection) {
        currentDirection = 3;
        flagMovement = true;
    }
    x += speed * elapsedTime;
}

void Player::update(float elapsedTime) {
    this->elapsedTime = elapsedTime;
}

void Player::draw() {
    const Texture& toDraw = Global::get().playerTexture[currentDirection][currentImage / 4];                      //0 = up, 1 = down, 2 = left, 3 = right
    DrawTexture(toDraw, int(x - (double)(toDraw.width - DUMMY_PLAYER_TEXTURE.width) / 2 + 0.5), 
                int(y - (toDraw.height - DUMMY_PLAYER_TEXTURE.height) + 0.5), WHITE);    
    if (flagMovement) {
        currentImage++;
        if (currentImage == 16) {       //For draw 4 images
            currentImage = 0;
        }
        flagMovement = false;
    } else {
        currentImage = 0;
    }
}

void Player::normalize() {
    x = std::min(x, (float)SCREEN_WIDTH - getWidth());
    x = std::max(x, ((float) getWidth() - DUMMY_PLAYER_TEXTURE.width) / 2);
    y = std::min(y, (float)SCREEN_HEIGHT - DUMMY_PLAYER_TEXTURE.height);
    y = std::max(y, (float) getHeight() - DUMMY_PLAYER_TEXTURE.height);
}

int Player::getcurrentY() {
    return y;
}