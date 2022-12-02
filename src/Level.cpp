#include "Level.h"

Level::Level() {
    player = new Player((float)10);
    over = won = false;
}

Level::~Level() {
    delete player;
}

void Level::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    player->draw();
    EndDrawing();
}

bool Level::isOver() {
    return over;
}

bool Level::isWon() {
    return won;
}

void Level::playerMoveUp() {
    if (over) {
        return;
    }
    player->moveUp();
}

void Level::playerMoveLeft() {
    if (over) {
        return;
    }
    player->moveLeft();
}

void Level::playerMoveDown() {
    if (over) {
        return;
    }
    player->moveDown();
}

void Level::playerMoveRight() {
    if (over) {
        return;
    }
    player->moveRight();
}