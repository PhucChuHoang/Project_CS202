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

CollisionType Lane::checkCollision(const Player& player) {
    CollisionType ret = COLLISION_TYPE_NONE;
    for (auto obs : obstancles) {
        ret = std::max(ret, obs->collision(player));
    }
    return ret;
}