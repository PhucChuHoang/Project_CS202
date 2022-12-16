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
    int getWidth();
    int getHeight();
    Texture getTexture();
    Rectangle getBoundaryRec() const;
    virtual ~Entity();
    virtual void update(float elapsedTime, TrafficLight* trafficLight = nullptr) = 0;
    virtual bool reset() = 0;
};
class MovingEntity: public Entity {
protected:
    float speed;
    float maxSpeed;
    MovingEntity(const Sound *_sound,const Texture& texture, float speed, float x = 0, float y = 0);
public:
    virtual ~MovingEntity() = default;
    CollisionType collision(const Entity& oth,bool playSound = false);
    void setMaxSpeed(float maxSpeed);
    void pauseEntity();
    void slowdown(float elapsedTime);
    void speedup(float elapsedTime);
    void update(float elapsedTime, TrafficLight* trafficLight = nullptr) override;
    bool reset() override;
};

class StaticEntity: public Entity {
protected:
    bool passable;
    StaticEntity(const Sound *_sound,const Texture& texture, bool passable, float x = 0, float y = 0);
public:
    virtual ~StaticEntity() = default;
    void update(float elapsedTime, TrafficLight* trafficLight = nullptr) override;
    bool reset() override;
    CollisionType collision(const Entity& oth, bool playSound  = false);
};

#endif