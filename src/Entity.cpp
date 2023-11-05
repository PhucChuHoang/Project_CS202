#include "Entity.h"
#include "Constants.h"
#include "TrafficLight.h"
#include "Random.h"
#include <iostream>

Entity::Entity(const Sound *_sound, const Texture& texture, float x, float y): texture(texture), x(x), y(y) {
    if(_sound != nullptr)
    {
    sound = new Sound;
    *sound = *_sound;
    }
    width = texture.width;
    height = texture.height;
} 

bool Entity::operator< (const Entity& oth) {
    return x < oth.x;
}

bool Entity::intersect(const Entity& oth, bool playSound){
    if (CheckCollisionRecs(getBoundaryRec(), oth.getBoundaryRec())) {
        if (playSound == true)
        {
            if (sound != nullptr) PlaySound(*sound);
            if (oth.sound != nullptr) PlaySound(*oth.sound);
        }
        return true;
    }
    return false;
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
Entity::~Entity() {}
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
        elapsedTime -= 0.003;
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
    if(trafficLight == nullptr) {
        speed = backupSpeed;
        return;
    }

    if(trafficLight->getLightState() == REDLIGHT) this->pauseEntity();
    else if (trafficLight->getLightState() == GREENLIGHT) this->speedup(elapsedTime);
    else if (trafficLight->getLightState() == YELLOWLIGHT) this->slowdown(elapsedTime);
}

bool MovingEntity::reset(Entity* const pre, float minSpeed, float maxSpeed) {
    if (pre == nullptr) {
        if (x < MIN_X) {
            x += (MAX_X - MIN_X);
            speed = Random::next(minSpeed, maxSpeed);
        }
        if (MAX_X < x) {
            x -= (MAX_X - MIN_X);
            speed = Random::next(minSpeed, maxSpeed);
        }
        return true;
    }
    bool flag = false;
    float distance, remain;
    if (x < MIN_X) {
        x += (MAX_X - MIN_X);
        distance = x - (((MovingEntity*)pre)->x + pre->getWidth());
        remain = ((MovingEntity*)pre)->x - MIN_X;
        distance = std::max(0.0f, distance);
        flag = true;
    }
    if (MAX_X < x) {
        x -= (MAX_X - MIN_X);
        distance = ((MovingEntity*)pre)->x - (x + getWidth());
        remain = MAX_X - ((MovingEntity*)pre)->x;
        distance = std::max(0.0f, distance);
        flag = true;
    }
    if (flag) {
        float t = remain / ((MovingEntity*)pre)->backupSpeed;
        float lo = minSpeed, hi = std::min(((MovingEntity*)pre)->backupSpeed + distance / t, maxSpeed);
        if (lo > hi) {
            backupSpeed = lo;
        }
        backupSpeed = Random::wnext(1, lo, hi);
        return false;
    }

    return true;
}

StaticEntity::StaticEntity(const Sound *_sound ,const Texture& texture, bool passable, float x, float y):
    Entity(_sound,texture, x, y), passable(passable) {};

void StaticEntity::update(float elapsedTime, TrafficLight* trafficLight) {
    // do nothing
}

bool StaticEntity::reset(Entity* const pre, float minSpeed, float maxSpeed) {
    // do nothing
    return true;
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