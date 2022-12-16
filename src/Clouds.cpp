#include "Clouds.h"
#include "Global.h"
#include "Random.h"

Clouds::Clouds(float x, float y): MovingEntity(nullptr, Global::get().cloudsTexture[Random::next(0, 3)], Random::next(2.0f, 5.0f), x, y), 
    originalX(x), startingX(x + Random::next((float)0, (float)20)), startingDirection(Random::next(0, 1)? DIRECTION_LEFT : DIRECTION_RIGHT) {}

void Clouds::reset() {
    x = startingX;
    curDirection = startingDirection;
}

void Clouds::update(float elapsedTime, TrafficLight* trafficLight) {
    if (curDirection == DIRECTION_RIGHT) {
        x += speed * elapsedTime;
    } else {
        x -= speed * elapsedTime;
    }
    while (x < originalX || x > originalX + 20) {
        if (curDirection == DIRECTION_RIGHT) {
            assert(x > originalX + 20);
            x = 2 * (originalX + 20) - x;
            curDirection = DIRECTION_LEFT;
        } else {
            assert(x < originalX);
            x = 2 * (originalX) - x;
            curDirection = DIRECTION_RIGHT;
        }
    }
}