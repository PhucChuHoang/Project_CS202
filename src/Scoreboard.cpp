#include"Scoreboard.h"
#include"Global.h"
#include<iostream>
InputPanel::InputPanel() {
    inputPanel = Global::get().scoreboard_inputPanel;
    returnButton = Global::get().returnButton;
    returnButtonHover = Global::get().returnButtonHover;
    returnButtonRect = { (float)SCREEN_WIDTH / 2 - returnButton.width / 2, (float)SCREEN_HEIGHT / 2 + 350, (float)returnButton.width, (float)returnButton.height };
    background = Global::get().background;
}

InputPanel::~InputPanel() {

}

int InputPanel::drawPanel(string& name) {
    BeginDrawing();
    ClearBackground(WHITE);
    mouseLocation = GetMousePosition();
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(inputPanel, SCREEN_WIDTH / 2 - inputPanel.width / 2, SCREEN_HEIGHT / 2 - inputPanel.height / 2, WHITE);
    if (CheckCollisionPointRec(mouseLocation, returnButtonRect)) {
        DrawTexture(returnButtonHover, SCREEN_WIDTH / 2 - returnButton.width / 2, SCREEN_HEIGHT / 2 + 350, WHITE);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 1;
        }
    } else {
        DrawTexture(returnButton, SCREEN_WIDTH / 2 - returnButton.width / 2, SCREEN_HEIGHT / 2 + 350, WHITE);
    }
    EndDrawing();
    return 0;
}

Scoreboard::Scoreboard() {
    title = Global::get().scoreboard_title;
    player = Global::get().scoreboard_player;
    level = Global::get().scoreboard_level;
    time = Global::get().scoreboard_time;
    board = Global::get().scoreboard_board;
    inputPanel = new InputPanel();
    

    returnButton = Global::get().returnButton;
    returnButtonHover = Global::get().returnButtonHover;
    returnButtonRect = { (float)SCREEN_WIDTH / 2 - returnButton.width / 2, (float)SCREEN_HEIGHT / 2 + 350, (float)returnButton.width, (float)returnButton.height };
    
    background = Global::get().background;

    std::ifstream input(SCOREBOARD_DATA);
    if(input.is_open()) {
        string line;
        while(std::getline(input, line)) {
            string player_name = line.substr(0, line.find_first_of(" "));
            line = line.substr(line.find_first_of(" ") + 1);
            int player_level = stoi(line.substr(0, line.find_first_of(" ")));
            line = line.substr(line.find_first_of(" ") + 1);
            double player_time = stod(line);
            players.push(Package(player_name, player_level, player_time));
            // std::cout << "Player " << player_name << " Level " << player_level << " Time " << player_time << std::endl;
        }
    }
    input.close();


    PLAYER_POSITION = {SCREEN_WIDTH / 2 - board.width / 2 + 90, SCREEN_HEIGHT / 2 - board.height / 2 + 20};
    LEVEL_POSITION = {SCREEN_WIDTH / 2 - board.width / 2 + player.width + 90 + 37, SCREEN_HEIGHT / 2 - board.height / 2 + 22};
    TIME_POSITION = {SCREEN_WIDTH / 2 - board.width / 2 + player.width + time.width + 37, SCREEN_HEIGHT / 2 - board.height / 2 + 22};
    BOARD_POSITION = {SCREEN_WIDTH / 2 - board.width / 2, SCREEN_HEIGHT / 2 - board.height / 2};
    TITLE_POSITION = {SCREEN_WIDTH / 2 - title.width / 2, SCREEN_HEIGHT / 2 - board.height / 2 - 90};
}

Scoreboard::~Scoreboard() {
    
}

int Scoreboard::drawScoreboard() {
    BeginDrawing();
    ClearBackground(WHITE);
    mouseLocation = GetMousePosition();
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(title, TITLE_POSITION.first, TITLE_POSITION.second, WHITE);
    DrawTexture(board, BOARD_POSITION.first, BOARD_POSITION.second, WHITE);
    DrawTexture(player, PLAYER_POSITION.first, PLAYER_POSITION.second, WHITE);
    DrawTexture(level, LEVEL_POSITION.first, LEVEL_POSITION.second, WHITE);
    DrawTexture(time,TIME_POSITION.first, TIME_POSITION.second, WHITE);

    std::priority_queue<Package, std::vector<Package>, Comparator> temp(players);
    while(!temp.empty()) {
        Package p = temp.top();
        int factor = temp.size() - 1;
        int hour = p.time / 60 / 60;
        int minute = (int) (p.time / 60) % 60;
        int second = (int)p.time % 60;
        DrawText(p.name.c_str(), PLAYER_POSITION.first + 50, PLAYER_POSITION.second + player.height + 31 + 99 * factor + 20, 35, BLACK);
        DrawText(std::to_string(p.level).c_str(), LEVEL_POSITION.first + 80, LEVEL_POSITION.second + level.height + 31 + 99 * factor + 20, 35, BLACK);
        DrawText((std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second)).c_str(), TIME_POSITION.first + 120, TIME_POSITION.second + time.height + 31 + 99 * factor + 20, 35, BLACK);
        temp.pop();
    }

    if (CheckCollisionPointRec(mouseLocation, returnButtonRect)) {
        DrawTexture(returnButtonHover, SCREEN_WIDTH / 2 - returnButton.width / 2, SCREEN_HEIGHT / 2 + 350, WHITE);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            PlaySound(Global::get().buttonClick);
            return 1;
        }
    } else {
        DrawTexture(returnButton, SCREEN_WIDTH / 2 - returnButton.width / 2, SCREEN_HEIGHT / 2 + 350, WHITE);
    }
    EndDrawing();
    return 0;
}

void Scoreboard::updateRanking(const Package& new_record) {
    players.push(new_record);
    players.pop();
    std::ofstream output(SCOREBOARD_DATA);
    if(output.is_open()) {
        std::priority_queue<Package, std::vector<Package>, Comparator> temp(players);
        while(!temp.empty()) {
            Package p = temp.top(); //
            output << p.name << " " << p.level << " " << p.time << std::endl;
            temp.pop();
        }
    }
    output.close();
}

int Scoreboard::renderNameInputPanel(string& name) {
    return inputPanel->drawPanel(name);
}