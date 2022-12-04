#include "Lane.h"
#include "Constants.h"
#include "Car.h"
#include "Rock.h"

Lane::Lane(Direction direction, float y): StaticEntity(ROAD_IMAGE, true, 0, y), direction(direction) {
    obstancles.push_back(new Car(500, direction, y));
    obstancles.push_back(new Rock(200, y));
}

Lane::~Lane() {
    // should implement
}

void Lane::draw() {
    // draw lane
    x = 0;
    while (x < SCREEN_WIDTH) {
        Entity::draw();
        x += getWidth();
    }

    // draw obstancle
    for (auto obs : obstancles) {
        obs->draw();
    }
}

void Lane::update(float elapsedTime) {
    for (auto obs : obstancles) {
        obs->update(elapsedTime);
    }

    // check outside + generate object : D
}

bool Lane::checkCollision(const Player& player) {
    for (auto obs : obstancles) {
        if (obs->intersect(player)) {
            return true;
        }
    }
    return false;
}