#include "raylib.h"
#include "main.h"
#include "musicplayer.h"

#include <iostream>


int main(void)
{
    

    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Conductor game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    InitAudioDevice();

    MusicPlayer player("../resources/rwbk.wav");
    MusicPlayer player2("../resources/rwbk.wav");
    //MusicPlayer player2("../resources/music2.wav");

    player.play();
    player2.play();
    //player2.play();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // TODO: Update your variables here
       
        const auto x = GetMouseX();

        const auto score = 2 * x / (float)GetScreenWidth();


        player.update(score);
        player2.update(0.0f);
        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hello world!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}