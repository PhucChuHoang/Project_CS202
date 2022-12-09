#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player: public MovingEntity {
private:
    float elapsedTime;
    int currentDirection;
    int currentImage;
    bool flagMovement;
public:
    Player(float speed);
    void moveUp(bool updateDirection = true);
    void moveDown(bool updateDirection = true);
    void moveLeft(bool updateDirection = true);
    void moveRight(bool updateDirection = true);
    void update(float elapsedTime);
    void draw();
    int getcurrentY();
};

#endif