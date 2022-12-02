#include "Player.h"
#include "Constants.h"

Player::Player(float speed): MovingEntity(PLAYER_IMAGE, speed) {}
void Player::moveUp() {
    y -= speed;
}
void Player::moveDown() {
    y += speed;
}
void Player::moveLeft() {
    x -= speed;
}
void Player::moveRight() {
    x += speed;
}