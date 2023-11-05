#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

using std::string;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const char* APP_NAME;

extern const char* PLAYER_IMAGE;
extern const char* CAR_IMAGE;
extern const char* ROCK_IMAGE;
extern const char* ROAD_IMAGE;
extern const char* WATER_PONDER_IMAGE;
extern const char* AMBULANCE_IMAGE;
extern const char* GRASS_IMAGE;
extern const char* SCOREBOARD_DATA;

extern const int MIN_X;
extern const int MAX_X;
extern const int PLAYER_SPEED[5];
extern const int PLAYER_VISION[5];
extern const int NUM_COIN_IN_ONE_LEVEL;
extern const int BONUS_COIN_WIN_LEVEL;
extern const int MAX_NUM_LANES;
extern const int LANES_UPPER_BOUND;
extern const int LANES_LOWER_BOUND;

extern const unsigned int RANDOM_SEED;
#endif