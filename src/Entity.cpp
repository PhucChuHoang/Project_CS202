#include "Entity.h"
#include "TrafficLight.h"

Entity::Entity(const Sound *_sound, const Texture& texture, float x, float y): texture(texture), x(x), y(y) {
    if(_sound != nullptr)
    {
    sound = new Sound;
    *sound = *_sound;
    }
    width = texture.width;
    height = texture.height;
} 

bool Entity::intersect(const Entity& oth, bool playSound){
    if (playSound == true)
    {
        if (sound != nullptr) PlaySound(*sound);
        if (oth.sound != nullptr) PlaySound(*sound);
    }
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
Entity::~Entity()
{
    if (sound != nullptr) delete sound;
}
MovingEntity::MovingEntity(const Sound *_sound, const Texture& texture, float speed, float x, float y):
    Entity(_sound,texture, x, y), speed(speed), backupSpeed(speed) {}


CollisionType MovingEntity::collision(const Entity& oth, bool playSound) {
    if (intersect(oth,playSound)) {
        return COLLISION_TYPE_MOVING;
    }
    return COLLISION_TYPE_NONE;
}

void MovingEntity::pauseEntity() {
    speed = 0;
}

void MovingEntity::slowdown(float elapsedTime) {
    while (elapsedTime >= 0.002) {
        speed = speed * 0.995;
        elapsedTime -= 0.002;
    }
}

void MovingEntity::speedup(float elapsedTime) {
    if (speed == backupSpeed) {
        return;
    }
    speed = std::max(speed, 5.0f);
    while (elapsedTime >= 0.002) {
        speed = speed * 1.005;
        elapsedTime -= 0.002;
    }
    speed = std::min(speed, backupSpeed);
}

void MovingEntity::update(float elapsedTime, TrafficLight* trafficLight) {
    if(trafficLight == nullptr) return;
    if(trafficLight->getLightState() == REDLIGHT) this->pauseEntity();
    else if (trafficLight->getLightState() == GREENLIGHT) this->speedup(elapsedTime);
    else if (trafficLight->getLightState() == YELLOWLIGHT) this->slowdown(elapsedTime);
}

StaticEntity::StaticEntity(const Sound *_sound ,const Texture& texture, bool passable, float x, float y):
    Entity(_sound,texture, x, y), passable(passable) {};

void StaticEntity::update(float elapsedTime, TrafficLight* trafficLight) {
    // do nothing
}

CollisionType StaticEntity::collision(const Entity& oth, bool playSound) {
    if (intersect(oth,playSound)) {
        if (passable) {
            return COLLISION_TYPE_PASSABLE;
        } else {
            return COLLISION_TYPE_UNPASSABLE;
        }
    }
    return COLLISION_TYPE_NONE;
}