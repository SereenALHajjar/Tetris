#include <raylib.h>
#include "Game.hpp"
#include <iostream>
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 620;
const Color DARK_BLUE = {0, 0, 26, 255};
double lastUpdateTime = 0;

bool EventTrigger(double interval)
{
    int current_time = GetTime();
    if (current_time - lastUpdateTime >= interval)
    {
        lastUpdateTime = current_time;
        return true;
    }
    return false;
}
int main()
{

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
    SetTargetFPS(60);
    Game game = Game();
    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        UpdateMusicStream(game.music);
        // event handling
        game.HandleInput();
        // updating
        if (EventTrigger(0.02))
            game.MoveBlockDown();
        // drawing
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.game_over)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, darkGrey);
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, darkGrey);

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}