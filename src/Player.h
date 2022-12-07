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
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void update(float elapsedTime);
    void draw();
};

#endif