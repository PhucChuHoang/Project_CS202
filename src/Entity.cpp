#include "Entity.h"

Entity::Entity(string texturePath, float x, float y): x(x), y(y) {
    texture = LoadTexture(texturePath.c_str());
    width = texture.width;
    height = texture.height;
} 

bool Entity::intersect(const Entity& oth){
    return CheckCollisionRecs({x, y, (float)width, (float)height}, {oth.x, oth.y, (float)oth.width, (float)oth.height});
}

void Entity::draw() {
    DrawTexture(texture, int(x + 0.5), int(y + 0.5), WHITE);
}

Entity::~Entity() {
    UnloadTexture(texture);
}

MovingEntity::MovingEntity(string texturePath, float speed, float x, float y):
    Entity(texturePath, x, y), speed(speed) {};

StaticEntity::StaticEntity(string texturePath, bool passable, float x, float y):
    Entity(texturePath, x, y), passable(passable) {};

void StaticEntity::update(float elapsedTime) {
    // do nothing
}