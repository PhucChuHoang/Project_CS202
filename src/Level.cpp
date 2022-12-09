#include "Level.h"
#include <cassert>
#include "Global.h"
#include<iostream>
Level::Level()
{
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
Level::Level(int currentLevel)
{
    curTime = GetTime();
    player = new Player((float)500);

    // setup lane for each level

    vector<int> vectorRandomY;
    int numLane = 10;
    if (currentLevel < numLane)
    numLane = currentLevel;
    if (numLane <= 1) numLane = 3;
    
    for (int i = 1; i <= numLane; i++)
    {
        bool validRandom = true;
        int randomY = GetRandomValue(CHARACTOR_HEIGHT + 5, SCREEN_HEIGHT - 2*CHARACTOR_HEIGHT - 5);
        for (auto e : vectorRandomY)
            if (e + LANE_WIDTH + 5 >= randomY && randomY >= e - LANE_WIDTH - 5)
            {
                i--;
                validRandom = false;
                break;
            }
        if (validRandom == false)
        continue;
        vectorRandomY.push_back(randomY);
        if (i % 2 == 0)
            lanes.push_back(new Lane(DIRECTION_RIGHT, randomY));
        else
            lanes.push_back(new Lane(DIRECTION_LEFT, randomY));
    }
    std::cout<<lanes.size() << std::endl;
    // Random rocks

    // Setup traffic traffic_lights
    traffic_lights.push_back(new TrafficLight(Global::get().trafficLightTexture[0].width,
                                              Global::get().trafficLightTexture[0].height, Global::get().trafficLightTexture[0]));
    traffic_lights.push_back(new TrafficLight(Global::get().trafficLightTexture[1].width,
                                              Global::get().trafficLightTexture[1].height, Global::get().trafficLightTexture[1]));

    over = won = isRed = false;
    isInit = true;
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
    COUNT_FRAME++;
    if (COUNT_FRAME == 60)
    {
        COUNT_TIME++;
        COUNT_FRAME = 0;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // draw grass
    for (int y = 0; y < SCREEN_HEIGHT; y += GRASS_HEIGHT)
    {
        Grass grass(y);
        grass.draw();
    }

    if (!isRed && COUNT_TIME == 10)
    {
        COUNT_TIME = 0;
        // Toggle traffic lights
        traffic_lights[1]->draw();
        isRed = !isRed;
        for (int i = 0; i < lanes.size(); i++)
        {
            lanes[i]->toggleLaneState();
        }
    }
    else if (!isRed)
    {
        traffic_lights[0]->draw();
    }
    else if (isRed && COUNT_TIME == 2)
    {
        COUNT_TIME = 0;
        // Toggle traffic traffic lights
        traffic_lights[0]->draw();
        isRed = !isRed;
        for (int i = 0; i < lanes.size(); i++)
        {
            lanes[i]->toggleLaneState();
        }
    }
    else
    {
        traffic_lights[1]->draw();
    }
    for (auto lane : lanes)
    {
        lane->draw();
    }
    player->draw();
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
    if (!over)
    {
        return false;
    }
    return won;
}

bool Level::checkCollision(CollisionType type)
{
    for (auto lane : lanes)
    {
        if (lane->checkCollision(*player, type))
        {
            return true;
        }
    }
    return false;
}

void Level::update()
{
    assert(!over);

    float elapsedTime = GetTime() - curTime;
    curTime = GetTime();

    player->update(elapsedTime);
    for (auto lane : lanes)
    {
        lane->update(elapsedTime);
    }
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