#ifndef LANE_H
#define LANE_H

#include "Entity.h"
#include "Player.h"
#include "vector"

using std::vector;

class Lane: public StaticEntity {
private:
    Direction direction;
    vector<Entity*> obstancles;
public:
    Lane(Direction direction, float y);
    ~Lane();
    void draw();
    void update(float elapsedTime);
    bool checkCollision(const Player& player, CollisionType type);
};

#endif