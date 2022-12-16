#include <cassert>
#include "Lane.h"
#include "Constants.h"
#include "Car.h"
#include "Rock.h"
#include "Dog.h"
#include "Bird.h"
#include "WaterPond.h"
#include "Global.h"
#include "Random.h"
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
    int numCar = 3;
    //int speed = GetRandomValue(minSpeed, maxSpeed);
    for (int i = 0; i < numCar; i++)
    {
        vehicles.push_back(new Car(1000, direction, y));
        vehicles[i]->update(0.5*i);
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

    // draw vehicles
    for (auto obs : vehicles)
    {
        obs->draw();
    }
}

void Lane::update(float elapsedTime, TrafficLight* trafficLight)
{
    
    for (auto obs : vehicles)
    {
        obs->update(elapsedTime, trafficLight);
    }

    for (int i = 0; i < (int)vehicles.size(); ++i) {
        if (vehicles[i]->reset()) {
            vehicles[i]->setMaxSpeed(Random::next(500, 1000));
        }
    }
}

bool Lane::checkCollision(const Player &player, CollisionType type)
{
    for (auto obs : vehicles)
    {
        if (type == obs->collision(player))
        {
            obs->collision(player,true);
            return true;
        }
    }
    return false;
}

