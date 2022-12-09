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
    traffic_lights.push_back(new TrafficLight(Global::get().trafficLightTexture[1].width, 
                    Global::get().trafficLightTexture[1].height, Global::get().trafficLightTexture[1]));

    
    over = won = isRed = false;
    isInit = true;
}

Level::~Level() {
    for (auto lane: lanes) {
        delete lane;
    }
    delete player;
}

void Level::draw() {
    COUNT_FRAME++;
    if(COUNT_FRAME == 60) {
        COUNT_TIME++;
        COUNT_FRAME = 0;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (auto lane: lanes) {
        lane->draw();
    }
    player->draw();
   
    if(!isRed && COUNT_TIME == 10) {
        COUNT_TIME = 0;
        // Toggle traffic lights
        traffic_lights[1]->draw();
        isRed = !isRed;
    } else if(!isRed) {
        traffic_lights[0]->draw();
    } else if(isRed && COUNT_TIME == 2) {
        COUNT_TIME = 0;
        // Toggle traffic traffic lights
        traffic_lights[0]->draw();
        isRed = !isRed;
    } else {
        traffic_lights[1]->draw();
    }

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