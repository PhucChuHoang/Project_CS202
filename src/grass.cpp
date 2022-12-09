
#include"grass.h"

Grass::Grass(float y): StaticEntity(Global::get().grassTexture, true, 0, y) {
}

Grass::~Grass() {
    // should implement
}

void Grass::draw() {
    // draw lane
    assert(x == 0);
    while (x < SCREEN_WIDTH) {
        Entity::draw();
        x += getWidth();
    }
    x = 0;
}
