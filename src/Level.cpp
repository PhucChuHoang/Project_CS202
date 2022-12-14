#include "Level.h"
#include <cassert>
#include "Global.h"

#include"Dog.h"
#include"Rock.h"
#include"Bird.h"
#include"WaterPond.h"

#include<iostream>
Level::Level()
{
    curTime = GetTime();
    player = new Player((float)500);
    // Random lane
   // lanes.push_back(new Lane(DIRECTION_RIGHT, 500));
  //  lanes.push_back(new Lane(DIRECTION_LEFT, 300));



    // Setup traffic traffic_lights
    traffic_lights.push_back(new TrafficLight(Global::get().trafficLightTexture[0].width,
                                              Global::get().trafficLightTexture[0].height, Global::get().trafficLightTexture[0]));
    traffic_lights.push_back(new TrafficLight(Global::get().trafficLightTexture[1].width,
                                              Global::get().trafficLightTexture[1].height, Global::get().trafficLightTexture[1]));
    moving_obsticles.push_back(new Dog(50, DIRECTION_RIGHT, 40));
    moving_obsticles.push_back(new Dog(50, DIRECTION_LEFT, 90));
    moving_obsticles.push_back(new Bird(50, 40));
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
    if (numLane < 3) numLane = 3;
    
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
            lanes.push_back(new Lane(DIRECTION_RIGHT, randomY,currentLevel));
        else
            lanes.push_back(new Lane(DIRECTION_LEFT, randomY,currentLevel));
    }
    // Random rocks
    int N = (currentLevel <= 5) ? 10 : (currentLevel <= 10) ? 15: (currentLevel <= 15) ? 20: 25;
    int nMoving = GetRandomValue(0, N);
    int nStatic = N - nMoving;
    for(int i = 0; i < nStatic; i++) {
            int choice = GetRandomValue(0, 1);
            int gap = (choice == 0) ? Global::get().rockTexture.height: Global::get().waterPonderTexture.height;
            int height;
            do {
                height = GetRandomValue(0, 900 - gap);
            } while(!valid(height));
            if(choice == 0) static_obsticles.push_back(new Rock(GetRandomValue(Global::get().rockTexture.width, 1360 - Global::get().rockTexture.width), height));
            else if(choice == 1) static_obsticles.push_back(new Rock(GetRandomValue(Global::get().waterPonderTexture.width, 1360 - Global::get().waterPonderTexture.width), height));
    }

    for(int i = 0; i < nMoving; i++) {
            int choice = GetRandomValue(0, 1);
            int gap = (choice == 0) ? Global::get().dogTexture[0][0].height: Global::get().birdTexture[0].height;
            int height;
            do {
                height = GetRandomValue(0, 900 - gap);
            } while(!valid(height));
            Direction d = GetRandomValue(0,1) == 0 ? DIRECTION_LEFT : DIRECTION_RIGHT;
            if(choice == 0)  moving_obsticles.push_back(new Dog(GetRandomValue(0, 100), d, height));
            else if(choice == 1) moving_obsticles.push_back(new Bird(GetRandomValue(50, 100), height));
    }
    // Setup traffic traffic_lights
    traffic_lights.push_back(new TrafficLight(Global::get().trafficLightTexture[0].width,
                                              Global::get().trafficLightTexture[0].height, Global::get().trafficLightTexture[0]));
    traffic_lights.push_back(new TrafficLight(Global::get().trafficLightTexture[1].width,
                                              Global::get().trafficLightTexture[1].height, Global::get().trafficLightTexture[1]));

    
    for(int i = 0; i < 10; i++) {
        coins.push_back(new Coin(GetRandomValue(Global::get().coinTexture.width, 1360 - Global::get().coinTexture.width), GetRandomValue(0, 900), 10));
    }
    
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
        if (!CheckCollisionCircleRec(playerCenter, 400, cloud->getBoundaryRec())) {
            cloud->draw();
        }
    }


    if (!isRed && COUNT_TIME == 10)
    {
        COUNT_TIME = 0;
        // Toggle traffic lights
        traffic_lights[1]->draw();
        isRed = !isRed;
        for (int i = 0; i < (int)lanes.size(); i++)
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
        for (int i = 0; i < (int)lanes.size(); i++)
        {
            lanes[i]->toggleLaneState();
        }
    }
    else
    {
        traffic_lights[1]->draw();
    }

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
    

    player->update(elapsedTime);
    for (auto lane : lanes)
    {
        lane->update(elapsedTime);
    }
    for(auto obsticle: moving_obsticles){
        obsticle->update(elapsedTime);
    }
    for(auto obsticle: static_obsticles){
        obsticle->update(elapsedTime);
    }

    for (int i = 0; i < (int)coins.size(); ++i) {
        if (coins[i]->collision(*player)) {
            coins[i]->collision(*player,true);
            money += coins[i]->getValue();
            coins.erase(coins.begin() + i);
            --i;
        }
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