#include "Level.h"
#include <cassert>

Level::Level() {
    curTime = GetTime();
    player = new Player((float)500);
    car1 = new Car(200, DIRECTION_LEFT, GetScreenWidth(), 100);
    car2 = new Car(200, DIRECTION_RIGHT, -100, 200);
    rock = new Rock(400, 400);
    over = won = false;
}

Level::~Level() {
    delete car1;
    delete car2;
    delete rock;
    delete player;
}

void Level::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    car1->draw();
    car2->draw();
    rock->draw();
    player->draw();
    EndDrawing();
}

bool Level::isOver() {
    checkCollision();
    return over;
}

bool Level::isWon() {
    checkCollision();
    return won;
}

void Level::checkCollision() {
    if (over) {
        return;
    }
    if (player->intersect(*car1)) {
        over = true;
        won = false;
    }
    if (player->intersect(*car2)) {
        over = true;
        won = false;
    }
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
    if (player->intersect(*rock)) { // unpassable
        player->moveDown();
    }
}

void Level::playerMoveLeft() {
    assert(!over);
    player->moveLeft();
    if (player->intersect(*rock)) { // unpassable
        player->moveRight();
    }
}

void Level::playerMoveDown() {
    assert(!over);
    player->moveDown();
    if (player->intersect(*rock)) { // unpassable
        player->moveUp();
    }
}

void Level::playerMoveRight() {
    assert(!over);
    player->moveRight();
    if (player->intersect(*rock)) { // unpassable
        player->moveLeft();
    }
}