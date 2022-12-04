#include <cassert>
#include "Lane.h"
#include "Constants.h"
#include "Car.h"
#include "Rock.h"

Lane::Lane(Direction direction, float y): StaticEntity(ROAD_IMAGE, true, 0, y), direction(direction) {
    obstancles.push_back(new Rock(200, y));
    obstancles.push_back(new Car(500, direction, y));
}

Lane::~Lane() {
    // should implement
}

void Lane::draw() {
    // draw lane
    assert(x == 0);
    while (x < SCREEN_WIDTH) {
        Entity::draw();
        x += getWidth();
    }
    x = 0;

    // draw obstancle
    for (auto obs : obstancles) {
        obs->draw();
    }
}

#include <iostream>
void Lane::update(float elapsedTime) {
    for (auto obs : obstancles) {
        obs->update(elapsedTime);
    }

    // check outside + generate object : D
}

bool Lane::checkCollision(const Player& player, CollisionType type) {
    for (auto obs : obstancles) {
        if (type == obs->collision(player)) {
            return true;
        }
    }
    return false;
}