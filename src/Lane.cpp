#include <cassert>
#include "Lane.h"
#include "Constants.h"
#include "Car.h"
#include "Rock.h"
#include "Dog.h"
#include "Bird.h"
#include "WaterPond.h"
#include "Global.h"
Lane::Lane(Direction direction, float y, const int &currentLevel) : StaticEntity(nullptr,Global::get().roadTexture, true, 0, y), direction(direction)
{
    // obstancles.push_back(new Car(500, direction, y));
    int minSpeed, maxSpeed;
    if (1 <= currentLevel && currentLevel <= 5)
    {
        minSpeed = 250;
        maxSpeed = 600;
    }
    if (6 <= currentLevel && currentLevel <= 10)
    {
        minSpeed = 600;
        maxSpeed = 900;
    }
    if (11 <= currentLevel && currentLevel <= 15)
    {
        minSpeed = 900;
        maxSpeed = 1200;
    }
    else
    {
        minSpeed = 1200;
        maxSpeed = 2100;
    }
    int numCar = GetRandomValue(1, 3);
    int speed = GetRandomValue(minSpeed, maxSpeed);
    for (int i = 0; i < numCar; i++)
    {
        obstancles.push_back(new Car(speed, direction, y));
        for (int j = 0; j < i; j++)
            while (obstancles[i]->intersect(*obstancles[j]) == true)
                {
                    obstancles[i]->update(GetRandomValue(1,100));
                }
    }
}

Lane::~Lane()
{
    // should implement
}

void Lane::draw()
{
    // draw lane
    assert(x == 0);
    while (x < SCREEN_WIDTH)
    {
        Entity::draw();
        x += getWidth();
    }
    x = 0;

    // draw obstancle
    for (auto obs : obstancles)
    {
        obs->draw();
    }
}

void Lane::update(float elapsedTime)
{
    for (auto obs : obstancles)
    {
        obs->update(elapsedTime);
    }

    Rectangle laneRec = getBoundaryRec();
    laneRec.width = SCREEN_WIDTH;
    // offset to ensure new object always intersect
    laneRec.x -= 5;
    laneRec.width += 10;

    for (int i = 0; i < (int)obstancles.size(); ++i)
    {
        if (!CheckCollisionRecs(laneRec, obstancles[i]->getBoundaryRec()))
        {
            delete obstancles[i];
            obstancles.erase(obstancles.begin() + i);
            obstancles.push_back(new Car(500, direction, y));
            --i;
        }
    }

    // check outside + generate object : D
}

bool Lane::checkCollision(const Player &player, CollisionType type)
{
    for (auto obs : obstancles)
    {
        if (type == obs->collision(player))
        {
            obs->collision(player,true);
            return true;
        }
    }
    return false;
}

void Lane::toggleLaneState()
{
    for (int i = 0; i < (int)obstancles.size(); i++)
        obstancles[i]->toggleState();
}
