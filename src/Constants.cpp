#include "Constants.h"
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 900;
const char* APP_NAME = "Crossing Road";

// const char* PLAYER_IMAGE = "img/player.png";
const char* CAR_IMAGE = "img/player.png";
const char* ROCK_IMAGE = "img/images/rock.png";
const char* ROAD_IMAGE = "img/images/road.png";
const char* WATER_PONDER_IMAGE = "img/images/water_pond.png";
const char* AMBULANCE_IMAGE = "img/images/Ambulance_right.png";
const char* GRASS_IMAGE = "img/images/Grass.png";
const char* SCOREBOARD_DATA = "data/scoreboard.txt";

const int MIN_X = -200;
const int MAX_X = SCREEN_WIDTH;
const int PLAYER_SPEED[5] = {150, 190, 255, 345, 500};
const int PLAYER_VISION[5] = {300, 400, 500, 600, 700};

const unsigned RANDOM_SEED = 0x12345678;