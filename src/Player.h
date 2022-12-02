#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player: public MovingEntity {
private:

public:
    Player(float speed);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};

#endif