#include "Player.h"
#include "Constants.h"
#include "Global.h"

Player::Player(float speed): MovingEntity(Global::get().playerTexture, speed) {}
void Player::moveUp() {
    y -= speed * elapsedTime;
}
void Player::moveDown() {
    y += speed * elapsedTime;
}
void Player::moveLeft() {
    x -= speed * elapsedTime;
}
void Player::moveRight() {
    x += speed * elapsedTime;
}

void Player::update(float elapsedTime) {
    this->elapsedTime = elapsedTime;
}