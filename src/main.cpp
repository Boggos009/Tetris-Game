#include <raylib.h>
#include <iostream>
#include "Colors.h"
#include "game.h"
using namespace std;


double lastTimeUpdated=0;
bool isEvenTrigged(double interval)
{
    double currentTime = GetTime();
    if(currentTime-lastTimeUpdated >=interval)
    {
        lastTimeUpdated = currentTime;
        return true;
    }
    return false;
}


int main() 
{
    InitWindow(500,620 , "Tetris");
    SetTargetFPS(60);
    Game game = Game();
    
    Font font = LoadFontEx("monogram.ttf" , 64 , 0 ,0);
    
    while(WindowShouldClose()==false)
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        
        if(isEvenTrigged(0.2))
        {
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);

        DrawTextEx(font , "Score" , {365 , 15} , 38 , 2 , WHITE);
        DrawTextEx(font , "Next" , {375 , 175} , 38 , 2 , WHITE);
        if(game.gameOver)
        {
            DrawTextEx(font , "GAME OVER" , {320 , 450} , 38 , 2 , WHITE);
        }
        DrawRectangleRounded({320,55,170,60} , 0.3 , 6 , lightBlue);
        
        char scoreText[10];
        sprintf(scoreText , "%d" , game.score);
        Vector2 textSize =  MeasureTextEx(font , scoreText , 38 , 2);
        DrawTextEx(font , scoreText , {320+(170-textSize.x)/2 , 65} , 32 , 2 , WHITE);
        
        DrawRectangleRounded({320,215,170,180} , 0.3 , 6 , lightBlue);

        game.Draw();
        EndDrawing();
    }


    CloseWindow();
}