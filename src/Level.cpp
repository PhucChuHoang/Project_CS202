#include "Level.h"
#include <cassert>

Level::Level() {
    curTime = GetTime();
    player = new Player((float)500);
    lanes.push_back(new Lane(DIRECTION_RIGHT, 500));
    lanes.push_back(new Lane(DIRECTION_LEFT, 300));
    over = won = false;
}

Level::~Level() {
    for (auto lane: lanes) {
        delete lane;
    }
    delete player;
}

void Level::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (auto lane: lanes) {
        lane->draw();
    }
    player->draw();
    EndDrawing();
}

bool Level::isOver() {
    if (!over && checkCollision(COLLISION_TYPE_MOVING)) {
        over = true;
    }   
    return over;
}

bool Level::isWon() {
    if (!over) {
        return false;
    }
    return won;
}

bool Level::checkCollision(CollisionType type) {
    for (auto lane: lanes) {
        if (lane->checkCollision(*player, type)) {
            return true;
        }
    }
    return false;
}

void Level::update() {
    assert(!over);

    float elapsedTime = GetTime() - curTime;
    curTime = GetTime();

    player->update(elapsedTime);
    for (auto lane: lanes) {
        lane->update(elapsedTime);
    }
}

void Level::playerMoveUp() {
    assert(!over);
    player->moveUp();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE)) { // unpassable
        player->moveDown();
    }
}

void Level::playerMoveLeft() {
    assert(!over);
    player->moveLeft();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE)) { // unpassable
        player->moveRight();
    }
}

void Level::playerMoveDown() {
    assert(!over);
    player->moveDown();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE)) { // unpassable
        player->moveUp();
    }
}

void Level::playerMoveRight() {
    assert(!over);
    player->moveRight();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE)) { // unpassable
        player->moveLeft();
    }
}