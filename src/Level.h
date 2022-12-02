#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Player.h"
#include "Car.h"

const int MAX_NUM_LANE = 12;
const int LANE_WIDTH = 50;

using std::vector;

class Level {
private:
    Player *player;
    Car* car1;
    Car* car2;
    bool over, won;
    double curTime;
public:
    Level();
    ~Level();
    void draw();
    bool isOver();
    bool isWon();
    void update();
    void playerMoveUp();
    void playerMoveLeft();
    void playerMoveDown();
    void playerMoveRight();
};

#endif