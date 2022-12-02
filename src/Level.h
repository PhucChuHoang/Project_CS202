#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Player.h"

const int MAX_NUM_LANE = 12;
const int LANE_WIDTH = 50;

using std::vector;

class Level {
private:
    Player *player;
    bool over, won;
public:
    Level();
    ~Level();
    void draw();
    bool isOver();
    bool isWon();
    void playerMoveUp();
    void playerMoveLeft();
    void playerMoveDown();
    void playerMoveRight();
};

#endif