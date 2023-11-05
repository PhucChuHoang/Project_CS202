 #ifndef LANE_H
#define LANE_H

#include "Entity.h"
#include "Random.h"
#include "Player.h"
#include <vector>

using std::vector;

enum LaneType {
    LANE_TYPE_OBSTANCLE = 0,
    LANE_TYPE_VEHICLE = 1,
    LANE_TYPE_ANIMAL = 2,
    LANE_TYPE_BIRD = 3
};

class Lane: public StaticEntity {
private:
    LaneType type;
    Direction direction;
    vector<Entity*> obstancle;
    float minSpeed, maxSpeed;
    Random::State randomState;
public:
    Lane(LaneType type, float y, int num, Direction direction = DIRECTION_LEFT, float minSpeed = 0, float MaxSpeed = 0);
    ~Lane();
    void draw() override;
    void update(float elapsedTime, TrafficLight* trafficLight = nullptr) override;
    bool checkCollision(const Entity& entity, CollisionType type, bool playSound = false);
};

#endif