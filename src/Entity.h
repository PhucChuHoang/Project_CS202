#ifndef ENTITY_H
#define ENTITY_H
#include <raylib.h>
#include <string>
using std::string;

enum Direction {
    DIRECTION_LEFT,
    DIRECTION_RIGHT
};

enum CollisionType {
    COLLISION_TYPE_NONE = 0,
    COLLISION_TYPE_PASSABLE = 1,
    COLLISION_TYPE_UNPASSABLE = 2,
    COLLISION_TYPE_MOVING = 3
};

class TrafficLight;

class Entity {
private:
    Sound *sound = nullptr;
    const Texture& texture;
    int width, height;
protected:
    float x, y;
    Entity(const Sound *_sound, const Texture& texture, float x = 0, float y = 0);
public:
    bool intersect(const Entity& oth, bool playSound = false);
    virtual CollisionType collision(const Entity& oth,bool playSound = false) = 0;
    virtual void draw();
    virtual void pauseEntity() = 0;
    virtual void resumeEntity() = 0;
    virtual void slowdown() = 0;
    int getWidth();
    int getHeight();
    Texture getTexture();
    Rectangle getBoundaryRec() const;
    virtual ~Entity();
    virtual void update(float elapsedTime, TrafficLight* trafficLight = nullptr) = 0;

};
class MovingEntity: public Entity {
protected:
    float speed;
    float backupSpeed;
    MovingEntity(const Sound *_sound,const Texture& texture, float speed, float x = 0, float y = 0);
public:
    virtual ~MovingEntity() = default;
    CollisionType collision(const Entity& oth,bool playSound = false);
    void pauseEntity() override;
    void resumeEntity() override;
    void slowdown() override;
    void update(float elapsedTime, TrafficLight* trafficLight = nullptr) override;
};

class StaticEntity: public Entity {
protected:
    bool passable;
    StaticEntity(const Sound *_sound,const Texture& texture, bool passable, float x = 0, float y = 0);
public:
    virtual ~StaticEntity() = default;
    void update(float elapsedTime, TrafficLight* trafficLight = nullptr) override;
    CollisionType collision(const Entity& oth, bool playSound  = false);
    void pauseEntity() override;
    void resumeEntity() override;
    void slowdown() override;
};

#endif