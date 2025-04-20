#include <iostream>
#include <raylib.h>
#include "game.hpp"

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Simple Platformer");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose() && game.run) {
        float dt = GetFrameTime();

        game.Update(dt);
        BeginDrawing();
        ClearBackground(SKYBLUE);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}