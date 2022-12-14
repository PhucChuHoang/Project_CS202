#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include "Player.h"
#include "Car.h"
#include "Rock.h"
#include "Lane.h"
#include "TrafficLight.h"
#include "grass.h"
#include "Coin.h"
const int MAX_NUM_LANE = 12;
const int LANE_WIDTH = 50;
const int GRASS_WIDTH = 300;
const int GRASS_HEIGHT = 300;
const int CHARACTOR_HEIGHT = 60;
using std::vector;

class Level {
private:
    Player *player;
    vector<Lane*> lanes;

    vector<TrafficLight*> traffic_lights;

    vector<StaticEntity*> static_obsticles;
    
    vector<MovingEntity*> moving_obsticles;

    vector<Coin*> coins;

    bool over, won, isRed, isInit;
    double curTime, totalTime;

    bool valid(int y);
public:
    Level();
    Level(int currentLevel);
    ~Level();
    void draw();
    bool isOver();
    bool isWon();
    void update(int& money, bool isPause);
    bool checkCollision(CollisionType type,bool playSound = false);
    void playerMoveUp();
    void playerMoveLeft();
    void playerMoveDown();
    void playerMoveRight();
    double getPlayedTime();
    static int COUNT_FRAME;
    static int COUNT_TIME;
};

#endif