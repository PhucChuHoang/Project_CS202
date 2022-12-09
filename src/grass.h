
#ifndef GRASS_H
#define GRASS_H
#include <cassert>
#include "Entity.h"
#include "Player.h"
#include "vector"
#include"Global.h"
using std::vector;


class Grass: public StaticEntity {
public:
    Grass(float y);
    void draw();
    ~Grass();
};

#endif