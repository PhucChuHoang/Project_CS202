#include "Entity.h"

Entity::Entity(const Texture& texture, float x, float y): texture(texture), x(x), y(y) {
    width = texture.width;
    height = texture.height;
} 

bool Entity::intersect(const Entity& oth){
    return CheckCollisionRecs(getBoundaryRec(), oth.getBoundaryRec());
}

int Entity::getWidth() {
    return width;
}
int Entity::getHeight() {
    return height;
}

Texture Entity::getTexture() {
    return texture;
}

Rectangle Entity::getBoundaryRec() const {
    return {x, y, (float)width, (float)height};
}

void Entity::draw() {
    DrawTexture(texture, int(x + 0.5), int(y + 0.5), WHITE);
}

MovingEntity::MovingEntity(const Texture& texture, float speed, float x, float y):
    Entity(texture, x, y), speed(speed) {};

CollisionType MovingEntity::collision(const Entity& oth) {
    if (intersect(oth)) {
        return COLLISION_TYPE_MOVING;
    }
    return COLLISION_TYPE_NONE;
}

StaticEntity::StaticEntity(const Texture& texture, bool passable, float x, float y):
    Entity(texture, x, y), passable(passable) {};

void StaticEntity::update(float elapsedTime) {
    // do nothing
}

CollisionType StaticEntity::collision(const Entity& oth) {
    if (intersect(oth)) {
        if (passable) {
            return COLLISION_TYPE_PASSABLE;
        } else {
            return COLLISION_TYPE_UNPASSABLE;
        }
    }
    return COLLISION_TYPE_NONE;
}

