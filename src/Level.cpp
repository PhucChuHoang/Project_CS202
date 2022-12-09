#include "Level.h"
#include <cassert>
#include"Global.h"
Level::Level() {
    curTime = GetTime();
    player = new Player((float)500);

    // Random lane
    lanes.push_back(new Lane(DIRECTION_RIGHT, 500));
    lanes.push_back(new Lane(DIRECTION_LEFT, 300));

    // Random rocks
    
    // Setup traffic traffic_lights
    traffic_lights.push_back(new TrafficLight(Global::get().trafficLightTexture[0].width, 
                    Global::get().trafficLightTexture[0].height, Global::get().trafficLightTexture[0]));
    traffic_lights.push_back(new TrafficLight(Global::get().trafficLightTexture[0].width, 
                    Global::get().trafficLightTexture[0].height, Global::get().trafficLightTexture[1]));

    
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
        player->moveDown(false);
    }
}

void Level::playerMoveLeft() {
    assert(!over);
    player->moveLeft();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE)) { // unpassable
        player->moveRight(false);
    }
}

void Level::playerMoveDown() {
    assert(!over);
    player->moveDown();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE)) { // unpassable
        player->moveUp(false);
    }
}

void Level::playerMoveRight() {
    assert(!over);
    player->moveRight();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE)) { // unpassable
        player->moveLeft(false);
    }
}