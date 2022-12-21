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

const int GRASS_WIDTH = 300;
const int GRASS_HEIGHT = 300;
using std::vector;

class Level {
private:
    Player *player;
    TrafficLight* traffic_lights;
    vector<Lane*> lanes;
    vector<Coin*> coins;

    bool over, won;
    double curTime, totalTime;

public:
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
};

#endif