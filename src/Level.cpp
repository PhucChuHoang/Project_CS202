#include "Level.h"
#include <cassert>

Level::Level() {
    curTime = GetTime();
    player = new Player((float)500);
    car1 = new Car(200, DIRECTION_LEFT, GetScreenWidth(), 100);
    car2 = new Car(200, DIRECTION_RIGHT, -100, 200);
    over = won = false;
}

Level::~Level() {
    delete player;
}

void Level::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    car1->draw();
    car2->draw();
    player->draw();
    EndDrawing();
}

bool Level::isOver() {
    return over;
}

bool Level::isWon() {
    return won;
}

void Level::update() {
    assert(!over);

    float elapsedTime = GetTime() - curTime;
    curTime = GetTime();

    car1->update(elapsedTime);
    car2->update(elapsedTime);
    player->update(elapsedTime);
}

void Level::playerMoveUp() {
    assert(!over);
    player->moveUp();
}

void Level::playerMoveLeft() {
    assert(!over);
    player->moveLeft();
}

void Level::playerMoveDown() {
    assert(!over);
    player->moveDown();
}

void Level::playerMoveRight() {
    assert(!over);
    player->moveRight();
}