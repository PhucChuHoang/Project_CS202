#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Player.h"
#include "Car.h"
#include "Rock.h"
#include "Lane.h"
#include"TrafficLight.h"
#include"grass.h"
const int MAX_NUM_LANE = 12;
const int LANE_WIDTH = 50;
const int GRASS_WIDTH = 300;
const int GRASS_HEIGHT = 300;
using std::vector;

class Level {
private:
    Player *player;
    vector<Lane*> lanes;
    vector<Rock*> rocks;
    vector<TrafficLight*> traffic_lights;
    bool over, won, isRed, isInit;
    double curTime;
    int curLevel = 1;
public:
    Level();
    ~Level();
    void draw();
    bool isOver();
    bool isWon();
    void update();
    bool checkCollision(CollisionType type);
    void playerMoveUp();
    void playerMoveLeft();
    void playerMoveDown();
    void playerMoveRight();
    static int COUNT_FRAME;
    static int COUNT_TIME;
};

#endif