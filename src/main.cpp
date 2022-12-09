#include "Game.h"
#include "Global.h"
using namespace std;
int Level::COUNT_FRAME = 0;
int Level::COUNT_TIME = 0;
int main(void) {
    Game game;
    game.run();
    return 0;
}   