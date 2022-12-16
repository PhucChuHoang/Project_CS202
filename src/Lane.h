 #ifndef LANE_H
#define LANE_H

#include "Entity.h"
#include "Player.h"
#include "vector"

using std::vector;

class Lane: public StaticEntity {
private:
    Direction direction;
    vector<MovingEntity*> vehicles;
public:
    Lane(Direction direction, float y,const int &currentLevel);
    ~Lane();
    void draw() override;
    void update(float elapsedTime, TrafficLight* trafficLight = nullptr) override;
    bool checkCollision(const Player& player, CollisionType type);
};

#endif