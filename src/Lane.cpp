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
Lane::Lane(LaneType type, float y, int num, Direction direction, float minSpeed, float maxSpeed): StaticEntity(nullptr, Global::get().roadTexture, true, 0, y), direction(direction), minSpeed(minSpeed), maxSpeed(maxSpeed) {
    
    Random::next();

    while (true) {
        bool ok = true;
        for (int i = 0; i < num; i++) {
            obstancle.push_back(new Car(minSpeed, direction, y));
            obstancle[i]->update(Random::next(0.0f, float((MAX_X - MIN_X) / minSpeed)));
        }
    
        for (int i = 0; i < num; i++) {
            for (int j = i + 1; j < num; ++j) {
                if (obstancle[i]->intersect(*obstancle[j])) {
                    ok = false;
                }
            }
        }
        if (ok) {
            std::sort(obstancle.begin(), obstancle.end(), [](const auto& a, const auto& b){
                return (*a) < (*b);
            });
            if (direction == DIRECTION_RIGHT) {
                std::reverse(obstancle.begin(), obstancle.end());
            }
            
            obstancle[0]->reset(nullptr, minSpeed, maxSpeed);
            for (int i = 1; i < num; ++i) {
                obstancle[i]->reset(obstancle[i - 1], minSpeed, maxSpeed);
            }
            break;
        } else {
            for (int i = 0; i < num; i++) {
                delete obstancle[i];
            }
            obstancle.clear();
        }
    }

    randomState = Random::getState();
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
    for (auto obs : obstancle)
    {
        obs->draw();
    }
}

void Lane::update(float elapsedTime, TrafficLight* trafficLight)
{
    Random::loadState(randomState);

    for (auto obs : obstancle)
    {
        obs->update(elapsedTime, trafficLight);
    }

    while (true) {
        std::sort(obstancle.begin(), obstancle.end(), [](const auto& a, const auto& b){
            return (*a) < (*b);
        });
        if (direction == DIRECTION_RIGHT) {
            std::reverse(obstancle.begin(), obstancle.end());
        }

        if (obstancle.size() == 1) {
            obstancle[0]->reset();
            break;
        } else if (obstancle[0]->reset(obstancle.back(), minSpeed, maxSpeed)) {
            break;
        }
    }
    
    randomState = Random::getState();
}

bool Lane::checkCollision(const Player &player, CollisionType type)
{
    for (auto obs : obstancle)
    {
        if (type == obs->collision(player))
        {
            obs->collision(player,true);
            return true;
        }
    }
    return false;
}

