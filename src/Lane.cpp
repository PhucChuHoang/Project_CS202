#include <cassert>
#include "Lane.h"
#include "Constants.h"
#include "Car.h"
#include "Rock.h"
#include "Global.h"

Lane::Lane(Direction direction, float y): StaticEntity(Global::get().roadTexture, true, 0, y), direction(direction) {
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

void Lane::update(float elapsedTime) {
    for (auto obs : obstancles) {
        obs->update(elapsedTime);
    }
    
    Rectangle laneRec = getBoundaryRec();
    laneRec.width = SCREEN_WIDTH;
    // offset to ensure new object always intersect
    laneRec.x -= 5;
    laneRec.width += 10;

    for (int i = 0; i < (int) obstancles.size(); ++i) {
        if (!CheckCollisionRecs(laneRec, obstancles[i]->getBoundaryRec())) {
            delete obstancles[i];
            obstancles.erase(obstancles.begin() + i);
            obstancles.push_back(new Car(3500, direction, y));
            --i;
        }
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

void Lane::toggleLaneState() {
    for(int i = 0; i < obstancles.size(); i++) obstancles[i]->toggleState();
}
