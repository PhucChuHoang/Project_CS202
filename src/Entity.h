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
class Entity {
private:
    Texture2D texture;
    int width, height;
protected:
    float x, y;
    Entity(string texturePath, float x = 0, float y = 0);
public:
    bool intersect(const Entity& oth);
    virtual CollisionType collision(const Entity& oth) = 0;
    void draw();
    int getWidth();
    int getHeight();
    Rectangle getBoundaryRec() const;
    virtual ~Entity();
    virtual void update(float elapsedTime) = 0;
};
class MovingEntity: public Entity {
protected:
    float speed;
    MovingEntity(string texturePath, float speed, float x = 0, float y = 0);
public:
    virtual ~MovingEntity() = default;
    CollisionType collision(const Entity& oth);
};

class StaticEntity: public Entity {
protected:
    bool passable;
    StaticEntity(string texturePath, bool passable, float x = 0, float y = 0);
public:
    virtual ~StaticEntity() = default;
    void update(float elapsedTime);
    CollisionType collision(const Entity& oth);
};

#endif