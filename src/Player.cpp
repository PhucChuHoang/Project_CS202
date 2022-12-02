#include "Player.h"
#include "Constants.h"

Player::Player(float speed): MovingEntity(PLAYER_IMAGE, speed) {}
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