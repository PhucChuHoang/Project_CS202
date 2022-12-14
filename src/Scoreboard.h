#pragma once
#include"Global.h"
#include<raylib.h>
#include<fstream>
#include<string>
#include<queue>
using std::string;

struct Package {
    string name;
    int level;
    double time;
    Package(string name, int level, double time) {
        this->name = name;
        this->level = level;
        this->time = time;
    }
    Package(const Package& other): name(other.name), level(other.level), time(other.time) {

    }
};

class Comparator {
public:
    bool operator() (const Package& p1, const Package& p2) const {
        if(p1.level > p2.level) return true;
        if(p1.level == p2.level) {
            return p1.time >= p2.time;
        }
        return false;
    }
};

class Scoreboard {
private:
    Texture2D board;
    Texture2D title, player, level, time;
    Texture2D returnButton;
    Texture2D returnButtonHover;
    Texture2D background;

    Vector2 mouseLocation;

    Rectangle returnButtonRect;

    std::priority_queue<Package, std::vector<Package>, Comparator> players;

    std::pair<int, int> PLAYER_POSITION;
    std::pair<int, int> LEVEL_POSITION;
    std::pair<int, int> TIME_POSITION;
    std::pair<int, int> BOARD_POSITION;
    std::pair<int, int> TITLE_POSITION;
public:
    Scoreboard();
    ~Scoreboard();
    int drawScoreboard();
    void renderNameInputPanel(string& name);
    void updateRanking(const Package& new_record);
};
