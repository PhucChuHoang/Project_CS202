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
const int NUM_COIN_IN_ONE_LEVEL = 10;
const int BONUS_COIN_WIN_LEVEL = 10; 
const int MAX_NUM_LANES = 15;
const int LANES_UPPER_BOUND = 50;
const int LANES_LOWER_BOUND = SCREEN_HEIGHT - 150;

const unsigned RANDOM_SEED = 0x12345678;