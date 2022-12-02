#ifndef ENTITY_H
#define ENTITY_H
#include <raylib.h>
#include <string>
using std::string;

enum Direction {
    DIRECTION_LEFT,
    DIRECTION_RIGHT
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
    void draw();
    virtual ~Entity();
    virtual void update(float elapsedTime) = 0;
};
class MovingEntity: public Entity {
protected:
    float speed;
    MovingEntity(string texturePath, float speed = 0, float x = 0, float y = 0);
public:
    virtual ~MovingEntity() = default;
};

#endif