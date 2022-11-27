#include "MainMenu.h"
using namespace std;

int main(void)
{
    const int screenWidth = 1366;
    const int screenHeight = 683;

    InitWindow(screenWidth, screenHeight, "Crossing Road");

    SetTargetFPS(60);   

    MainMenu mainMenu;            

    while (!WindowShouldClose())   
    {
        BeginDrawing();
            mainMenu.drawMenu();
        EndDrawing();
    }

    CloseWindow();    

    return 0;
}