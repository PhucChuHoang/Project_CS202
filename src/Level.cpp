#include "Level.h"
#include <cassert>
#include "Global.h"
#include "math.h"
#include "Dog.h"
#include "Rock.h"
#include "Bird.h"
#include "WaterPond.h"
Level::Level(int currentLevel, int currentSpeed)
{   
    Random::setLevelSeed(currentLevel);
    over = won = false;

    curTime = GetTime();
    over = won = false;
    player = new Player(PLAYER_SPEED[currentSpeed]);

    // Setup traffic traffic_lights
    traffic_lights = new TrafficLight(Global::get().trafficLightTexture[0].width,
                                              Global::get().trafficLightTexture[0].height);
    
    float reduceConst = 0.87;
    float baseSpeed = 150 * pow(1.03, currentLevel - 1);
    float carMinSpeed = baseSpeed;
    float carMaxSpeed = baseSpeed * 1.5;
    float animalMinSpeed = baseSpeed * 0.5;
    float animalMaxSpeed = baseSpeed * 0.75;

    int groundLane = std::min(MAX_NUM_LANES, (currentLevel + 3) / 4);
    int flyLane = std::min(MAX_NUM_LANES, (currentLevel + 4) / 5);
    int dogLane = Random::wnext(-1 - currentLevel / 15, 0, groundLane);
    vector<bool> used(MAX_NUM_LANES, false);
    vector<int> type(groundLane, 0);

    for (int i = 0; i < dogLane; ++i) {
        type[i] = 1;
    }
    for (int i = 1; i < groundLane; ++i) {
        std::swap(type[Random::next(0, i)], type[i]); 
    }

    for (int i = 0; i < groundLane; ++i) {
        int pos = Random::wwnext(-1, 0, MAX_NUM_LANES - 1, 7);
        while (used[pos]) {
            pos = Random::wwnext(-1, 0, MAX_NUM_LANES - 1, 7);
        }
        used[pos] = true;
        int num = Random::wnext(-2, 1, 6);
        float coef = pow(reduceConst, num - 1);
        lanes.push_back(new Lane(type[i]? LANE_TYPE_ANIMAL : LANE_TYPE_VEHICLE, LANES_UPPER_BOUND + pos * 50, num, 
            Random::next(0, 1)? DIRECTION_LEFT : DIRECTION_RIGHT, (type[i]? animalMinSpeed : carMinSpeed) * coef, 
            (type[i]? animalMaxSpeed : carMaxSpeed) * coef));
    }

    for (int pos = 0; pos < MAX_NUM_LANES; ++pos) {
        if (used[pos] || Random::next(0, 1)) {
            continue;
        }
        lanes.push_back(new Lane(LANE_TYPE_OBSTANCLE, LANES_UPPER_BOUND + pos * 50, Random::wnext(-3, 1, 8)));  
    }

    for (int i = 0; i < MAX_NUM_LANES; ++i) {
        used[i] = false;
    }
    for (int i = 0; i < flyLane; ++i) {
        int pos = Random::wwnext(-1, 0, MAX_NUM_LANES - 1, 7);
        while (used[pos]) {
            pos = Random::wwnext(-1, 0, MAX_NUM_LANES - 1, 7);
        }
        used[pos] = true;
        int num = Random::wnext(-2, 1, 6);
        float coef = pow(reduceConst, num - 1);
        lanes.push_back(new Lane(LANE_TYPE_BIRD, LANES_UPPER_BOUND + pos * 50, num, 
            Random::next(0, 1)? DIRECTION_LEFT : DIRECTION_RIGHT, animalMinSpeed * coef, animalMaxSpeed * coef));
    }

    // coin should be in the center of a lane;
    
    for (int i = 0; i < NUM_COIN_IN_ONE_LEVEL; ++i) {
        Coin* newCoin = new Coin(Random::wwnext(std::min(-1, -3 + currentLevel / 15), 0, SCREEN_WIDTH - 30, SCREEN_WIDTH / 2 - 15), lanes[Random::next(0, lanes.size() - 1)]->getBoundaryRec().y + 10, 1);
        bool ok = true;
        for (auto lane : lanes) {
            if (lane->checkCollision(*newCoin, COLLISION_TYPE_UNPASSABLE)) {
                ok = false;
            }
        }
        for (auto coin : coins) {
            if (coin->intersect(*newCoin)) {
                ok = false;
            }
        }
        if (ok) {
            coins.push_back(newCoin);
        } else {
            delete newCoin;
            --i;
        }
    }
}
Level::~Level()
{
    for (auto lane : lanes)
    {
        delete lane;
    }
    delete player;
}

void Level::draw(int currentVision, int currentLevel, int numLife)
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

    player->normalize();
    player->draw();

    Rectangle playerVisionRec = player->getBoundaryRec();
    Vector2 playerCenter = {playerVisionRec.x + playerVisionRec.width / 2, playerVisionRec.y + playerVisionRec.height / 2};
    for (auto cloud: Global::get().allClouds) {
        if (!CheckCollisionCircleRec(playerCenter, PLAYER_VISION[currentVision], cloud->getBoundaryRec())) {
            cloud->draw();
        }
    }

    traffic_lights->draw();
    DrawText(TextFormat("Level: %i", currentLevel), SCREEN_WIDTH - 230, 0, 50, BLACK);
    DrawTexture(Global::get().heartTexture, SCREEN_WIDTH - 200, 50, WHITE);
    DrawText(TextFormat("x %i", numLife), SCREEN_WIDTH - 135, 50, 50, BLACK);

    EndDrawing();
}

bool Level::isOver()
{
    if (!over && checkCollision(COLLISION_TYPE_MOVING, true))
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
        if (lane->checkCollision(*player, type, playSound))
        {
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

    for (int i = 0; i < (int)coins.size(); ++i) {
        if (coins[i]->collision(*player)) {
            coins[i]->collision(*player,true);
            money += coins[i]->getValue();
            delete coins[i];
            coins.erase(coins.begin() + i);
            --i;
        }
    }

    for (auto cloud: Global::get().allClouds) {
        cloud->update(elapsedTime, traffic_lights);
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

double Level::getPlayedTime() {
    return totalTime;
}