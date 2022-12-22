#include "Game.h"
#include "Constants.h"
#include "Global.h"

#define clearDummyFrame(); BeginDrawing(); EndDrawing();

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
    InitAudioDevice();
    SetTargetFPS(60);

    Global::initialize();
    state = GAME_STATE_MAIN_MENU;
    mainMenu = new MainMenu();
    settingsMenu = new SettingsMenu();
    scoreboardMenu = new Scoreboard();
    pauseMenu = new PauseMenu();
    winGameMenu = new WinGameMenu();
    shop = new Shop();
    saveSlotMenu = new SaveSlotMenu();
    load();
    money = 0;
    numLife = 3;
    speedLevel = 0;
    visionLevel = 0;
    currentLevel = 1;
    totalTime = 0;
    level = nullptr;
    isPause = false;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 6; ++j) {
            printf("%d ", data[i][j]);
        }
        std::cout << dataTime[i] << std::endl;
    }
}

void Game::run() {
    PlaySound(Global::get().backgroundSound);
    string name = "";
    while (!WindowShouldClose()) {
        SetWindowTitle((string(APP_NAME) + " (FPS: " + std::to_string(GetFPS()) + ")").c_str());
        switch (state) {
        case GAME_STATE_MAIN_MENU: {
            int currentState = mainMenu->showMenu();
            if (currentState == 1) {
                level = new Level(currentLevel,speedLevel);
                state = GAME_STATE_PLAYING;
                clearDummyFrame();
            }
            else if (currentState == 2) {
                state = GAME_STATE_LOADGAME;
                clearDummyFrame();
            }
            else if (currentState == 3) {
                state = GAME_STATE_SCOREBOARD;
                clearDummyFrame();
            }
            else if (currentState == 4) {
                state = GAME_STATE_SETTINGS;
                clearDummyFrame();
            }
            else if (currentState == 5) {
                state = GAME_STATE_EXIT;
                clearDummyFrame();
            }
            break;
        }
        case GAME_STATE_PLAYING:
        {
            if (!level->isOver()) {
                if (level->isWon()) {
                    totalTime += level->getPlayedTime();
                    delete level;
                    level = nullptr;
                    currentLevel++;
                    money += 10;
                    // winner will earn 10 coins
                    PlaySound(Global::get().winSound);
                    state = GAME_STATE_WON;
                    clearDummyFrame();
                    break;
                }
                level->update(money, isPause);
                if (isPause) {
                    int pauseState = pauseMenu->showMenu(); // 1: Resume, 2: Save, 3: Exit
                    if (pauseState == 1) {
                        isPause = false;
                    }
                    else if (pauseState == 2) {
                        state = GAME_STATE_CHOOSE_SAVE_SLOT;
                        isPause = false;
                        clearDummyFrame();
                    }
                    else if (pauseState == 3) {
                        state = GAME_STATE_MAIN_MENU;
                        clearDummyFrame();
                        delete level;
                        level = nullptr;
                        money = 0;
                        numLife = 3;
                        speedLevel = 0;
                        visionLevel = 0;
                        currentLevel = 1;
                        totalTime = 0;
                        isPause = false;
                    }
                    break;
                }
                else
                    level->draw(visionLevel);
                if (IsKeyPressed(KEY_P)) {
                    isPause = true;
                    break;
                }
                if (IsKeyDown(KEY_DOWN)) {
                    level->playerMoveDown();
                }
                if (IsKeyDown(KEY_UP)) {
                    level->playerMoveUp();
                }
                if (IsKeyDown(KEY_RIGHT)) {
                    level->playerMoveRight();
                }
                if (IsKeyDown(KEY_LEFT)) {
                    level->playerMoveLeft();
                }
            }
            else {
                
                if (numLife == 1)
                state = GAME_STATE_INPUTNAME;
                else 
                {
                    delete level;
                    level = new Level(currentLevel,speedLevel);
                    clearDummyFrame();
                    numLife--;
                }
                printf("%d\n",numLife);
                
                
            }
            break;
        }
        case GAME_STATE_INPUTNAME:
        {
            if (scoreboardMenu->renderNameInputPanel(name) == 1) {
                name = string(TextToLower(name.c_str()));

                Package new_record(name, currentLevel - 1, totalTime + level->getPlayedTime());
                scoreboardMenu->updateRanking(new_record);
                delete level;
                currentLevel = 1;
                level = nullptr;
                name.clear();
                state = GAME_STATE_MAIN_MENU;
            }
            else {
                int key_code;
                while ((key_code = GetKeyPressed()) != 0)
                {
                    if (key_code == KEY_BACKSPACE)
                        name = name.substr(0, name.length() - 1);
                    else if (key_code == KEY_SPACE || key_code == KEY_UP || key_code == KEY_DOWN || key_code == KEY_LEFT || key_code == KEY_RIGHT)
                        continue;
                    else if (name.length() < 15)
                        name += (char)key_code;
                }
            }
            break;
        }
        case GAME_STATE_WON:
        {
            int winGameState = winGameMenu->showGameMenu(); // 1: next Stage, 2: Shop, 3: Save and exit
            if (winGameState == 1) {
                level = new Level(currentLevel,speedLevel);
                state = GAME_STATE_PLAYING;
                clearDummyFrame();
            }
            else if (winGameState == 2) {
                state = GAME_STATE_SHOP;
                clearDummyFrame();
            }
            else if (winGameState == 3) {
                state = GAME_STATE_CHOOSE_SAVE_SLOT;
                clearDummyFrame();
            }
            break;
        }
        case GAME_STATE_SHOP:
        {
            int shopIndex = shop->shopDraw(money); // 1: life, 2: view, 3: speed, 4: return
            if (shopIndex == 1) {
                if (money >= 10)
                {
                    money -= 10;
                    numLife++;
                    PlaySound(Global::get().buyItem);
                }
                clearDummyFrame();
            }
            else if (shopIndex == 2) {
                if (money >= 8 && visionLevel < 4) {
                    money -= 8;
                    visionLevel++;
                    PlaySound(Global::get().buyItem);
                }
                clearDummyFrame();
            }
            else if (shopIndex == 3 && speedLevel < 4) {
                if (money >= 12) {
                    money -= 12;
                    speedLevel++;
                    PlaySound(Global::get().buyItem);
                }
                clearDummyFrame();
            }
            else if (shopIndex == 4) {
                state = GAME_STATE_WON;
                clearDummyFrame();
            }
            break;
        }
        case GAME_STATE_LOADGAME:
        {
            int slotIndex = saveSlotMenu->drawSaveSlotMenu(data, dataTime);
            if (slotIndex == 0) {
                break;
            }
            if (slotIndex == 4) {
                state = GAME_STATE_MAIN_MENU;
                clearDummyFrame();
                break;
            }
            if (data[slotIndex - 1][0] == 0) {
                break;
            }
            currentLevel = data[slotIndex - 1][1];
            money = data[slotIndex - 1][2];
            numLife = data[slotIndex - 1][3];
            speedLevel = data[slotIndex - 1][4];
            visionLevel = data[slotIndex - 1][5];
            totalTime = dataTime[slotIndex - 1];
            level = new Level(currentLevel,speedLevel);
            state = GAME_STATE_PLAYING;
            clearDummyFrame();
            break;
        }
        case GAME_STATE_SCOREBOARD:
        {
            // Initialize score
            if (scoreboardMenu->drawScoreboard() == 1) {
                state = GAME_STATE_MAIN_MENU;
                clearDummyFrame();
            }
            break;
        }
        case GAME_STATE_SETTINGS:
        {
            if (settingsMenu->drawSettings() == 1) {
                state = GAME_STATE_MAIN_MENU;
                
                clearDummyFrame();
            }
            break;
        }
        case GAME_STATE_EXIT:
        {
            CloseWindow();
            break;
        }
        case GAME_STATE_CHOOSE_SAVE_SLOT:
        {
            int slotIndex = saveSlotMenu->drawSaveSlotMenu(data, dataTime);
            if (slotIndex == 0) {
                break;
            }
            if (slotIndex == 4 && level != nullptr) {
                state = GAME_STATE_PLAYING;
                clearDummyFrame();
                break;
            }
            else if (slotIndex == 4 && level == nullptr) {
                state = GAME_STATE_WON;
                clearDummyFrame();
                break;
            }
            if (slotIndex == 1 || slotIndex == 2 || slotIndex == 3) {
                save(slotIndex);
                state = GAME_STATE_MAIN_MENU;
                clearDummyFrame();
                delete level;
                level = nullptr;
                money = 0;
                numLife = 3;
                speedLevel = 0;
                visionLevel = 0;
                currentLevel = 1;
                totalTime = 0;
            }
            break;
        }
        default:
            break;
        }
    }
}
void Game::increaseLevel() {
    currentLevel++;
}
void Game::setLevelIs1() {
    currentLevel = 1;
}
int Game::getLevel() {
    return currentLevel;
}
Game::~Game() {
    Global::deallocate();
    if (level != nullptr) {
        delete level;
    }
    if (mainMenu != nullptr)
        delete mainMenu;
    if (settingsMenu != nullptr)
        delete settingsMenu;
    if (scoreboardMenu != nullptr)
        delete scoreboardMenu;
    if (pauseMenu != nullptr)
        delete pauseMenu;
    if (winGameMenu != nullptr)
        delete winGameMenu;
    if (shop != nullptr)
        delete shop;
    CloseWindow();
}

void Game::save(int slotIndex) {
    data[slotIndex - 1][0] = 1;         //Mark that this slot has save file
    data[slotIndex - 1][1] = currentLevel;
    data[slotIndex - 1][2] = money;
    data[slotIndex - 1][3] = numLife;
    data[slotIndex - 1][4] = speedLevel;
    data[slotIndex - 1][5] = visionLevel;
    dataTime[slotIndex - 1] = (float)std::floor(totalTime * 100 + 0.5) / 100;
    std::cout << dataTime[slotIndex - 1] << std::endl;
    std::cout << std::floor(totalTime * 100 + 0.5) / 100 << std::endl;

    std::ofstream fout;
    fout.open("data/save.bin", std::ios::binary);
    if (fout.is_open()) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 6; ++j) {
                fout.write((char*)&data[i][j], sizeof(int));
            }
            fout.write(reinterpret_cast<char*>(&dataTime[i]), sizeof(float));
        }
    }
    fout.close();
}

void Game::load() {
    std::ifstream fin;
    fin.open("data/save.bin", std::ios::binary);        
    if (fin.is_open()) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 6; ++j) {
                int x;
                fin.read((char*)&x, sizeof(int));
                data[i][j] = x;
            }
            float temp;
            fin.read((char*)&temp, sizeof(float));
            dataTime[i] = temp;
        }
    }
    fin.close();
}