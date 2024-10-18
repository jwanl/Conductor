#include "raylib.h"
#include "main.h"
#include "graphics.h"

#include <iostream>
#include "level.h"

int main(void)
{
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Conductor game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    InitAudioDevice();

    auto music = LoadWave("../resources/music.wav");
    auto sound = LoadSoundFromWave(music);




    std::cout << IsSoundReady(sound) << "\n";

    PlaySound(sound);

    Level level;
    Camera camera = { 0 };
    camera.position = { -3.0f, 0.0f, 0.0f };    // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    Graphics::init();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        std::cout << GetFPS() << "\n";
        // TODO: Update your variables here
        level.update();

        // Pre-draw: Render to texture
        BeginTextureMode(Graphics::getTrackRenderTexture());
        Graphics::drawRenderTexture(level.getTrack());
        EndTextureMode();

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        Graphics::renderTrack();
        EndMode3D();

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}