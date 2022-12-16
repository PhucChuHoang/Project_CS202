#include "Level.h"
#include <cassert>
#include "Global.h"

#include"Dog.h"
#include"Rock.h"
#include"Bird.h"
#include"WaterPond.h"

Level::Level(int currentLevel)
{
    over = won = isRed = false;

    curTime = GetTime();
    over = won = isRed = false;
    player = new Player((float)500);

    // Setup traffic traffic_lights
    traffic_lights = new TrafficLight(Global::get().trafficLightTexture[0].width,
                                              Global::get().trafficLightTexture[0].height);
    
    moving_obsticles.push_back(new Dog(500, DIRECTION_LEFT, 500));
    lanes.push_back(new Lane(LANE_TYPE_VEHICLE, 200, 3, DIRECTION_LEFT, 500, 1000));
    lanes.push_back(new Lane(LANE_TYPE_VEHICLE, 250, 4, DIRECTION_RIGHT, 400, 600));
    
}
Level::~Level()
{
    for (auto lane : lanes)
    {
        delete lane;
    }
    delete player;
}

void Level::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // draw grass
    for (int y = 0; y < SCREEN_HEIGHT; y += GRASS_HEIGHT)
    {
        Grass grass(y);
        grass.draw();
    }

    
    for (auto lane : lanes)
    {
        lane->draw();
    }
    for(auto coin: coins) coin->draw();
    for(auto obsticle: moving_obsticles) obsticle->draw();
    for(auto obsticle: static_obsticles) obsticle->draw();

    player->normalize();
    player->draw();

    Rectangle playerVisionRec = player->getBoundaryRec();
    Vector2 playerCenter = {playerVisionRec.x + playerVisionRec.width / 2, playerVisionRec.y + playerVisionRec.height / 2};
    for (auto cloud: Global::get().allClouds) {
        if (!CheckCollisionCircleRec(playerCenter, PLAYER_VISION[4], cloud->getBoundaryRec())) {
            cloud->draw();
        }
    }

    traffic_lights->draw();

    EndDrawing();
}

bool Level::isOver()
{
    if (!over && checkCollision(COLLISION_TYPE_MOVING))
    {
        over = true;
    }
    return over;
}

bool Level::isWon()
{
    if (!over && player->getcurrentY() <= 0)
    {
        return true;
    }
    return false;
}

bool Level::checkCollision(CollisionType type, bool playSound)
{
    player->normalize();
    for (auto lane : lanes)
    {
        if (lane->checkCollision(*player, type))
        {
            return true;
        }
    }

    for(auto obs: moving_obsticles) {
        if(type == obs->collision(*player)) { 
            obs->collision(*player,true);
            return true;
        }
    }

    for(auto obs: static_obsticles) {
        if(type == obs->collision(*player)) {
            obs->collision(*player,true); 
            return true;
        }
    }
    return false;
}

void Level::update(int& money, bool isPaused)
{
    assert(!over);
    float elapsedTime = GetTime() - curTime;
    curTime = GetTime();
    if (isPaused) {
        return;
    }
    
    totalTime += elapsedTime;
    traffic_lights->update(elapsedTime);

    player->update(elapsedTime, traffic_lights);
    for (auto lane : lanes)
    {
        lane->update(elapsedTime, traffic_lights);
    }
    for(auto obsticle: moving_obsticles){
        obsticle->update(elapsedTime, traffic_lights);
    }
    for(auto obsticle: static_obsticles){
        obsticle->update(elapsedTime, traffic_lights);
    }

    for (int i = 0; i < (int)coins.size(); ++i) {
        if (coins[i]->collision(*player)) {
            coins[i]->collision(*player,true);
            money += coins[i]->getValue();
            coins.erase(coins.begin() + i);
            --i;
        }
    }

    for (auto cloud: Global::get().allClouds) {
        cloud->update(elapsedTime, traffic_lights);
    }

    // if(traffic_lights->toggleStateDrawing(COUNT_TIME)) {
    //     for (int i = 0; i < (int)lanes.size(); i++)
    //     {
    //             lanes[i]->toggleLaneState();
    //     }
    // }
}

void Level::playerMoveUp()
{
    assert(!over);
    player->moveUp();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE))
    { // unpassable
        player->moveDown(false);
    }
}

void Level::playerMoveLeft()
{
    assert(!over);
    player->moveLeft();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE))
    { // unpassable
        player->moveRight(false);
    }
}

void Level::playerMoveDown()
{
    assert(!over);
    player->moveDown();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE))
    { // unpassable
        player->moveUp(false);
    }
}

void Level::playerMoveRight()
{
    assert(!over);
    player->moveRight();
    if (checkCollision(COLLISION_TYPE_UNPASSABLE))
    { // unpassable
        player->moveLeft(false);
    }
}

bool Level::valid(int y) {
    if(y >= (SCREEN_HEIGHT - Global::get().playerTexture[0][0].height)) return false;
    for(int i = 0; i < (int)lanes.size(); i++) {
        if(y >= lanes[i]->getHeight() - 60 && y <= lanes[i]->getHeight() + 120) return false;
    }
    for(int i = 0; i < (int)static_obsticles.size(); i++) {
        if(y >= static_obsticles[i]->getHeight() - 50 && y <= static_obsticles[i]->getHeight() + 70) return false;
    }
    return true;
}

double Level::getPlayedTime() {
    return totalTime;
}