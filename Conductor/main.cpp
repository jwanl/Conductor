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

    InitWindow(screenWidth, screenHeight, "Super Conductor Bros");

    SetTargetFPS(30);               // Set our game to run at 60 frames-per-second

    InitAudioDevice();
    const char* music = "../resources/rwbk.wav";
    


    
    ToggleFullscreen();
   
   
  

    Level* level = new Level(music);

    

    Camera camera = { 0 };
    camera.position = { -3.0f, 0.0f, 0.0f };    // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    Graphics::init("../resources/background.png", 
        {"../resources/conductor_0.png", "../resources/conductor_1.png", "../resources/conductor_2.png"});

    level->play();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //std::cout << GetFPS() << "\n";
        // TODO: Update your variables here

        level->update();

        // Pre-draw: Render to texture
        BeginTextureMode(Graphics::getTrackRenderTexture());
        Graphics::drawRenderTexture(level->getTrack());
        EndTextureMode();
        
        


       

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        Graphics::drawBackground();

        BeginMode3D(camera);
        Graphics::renderTrack();
        EndMode3D();

        Graphics::drawConductor(*level);

        const auto text_x = GetScreenWidth() * 0.6;
        const auto text_y = GetScreenHeight() * 0.1;
        DrawText(TextFormat("POINTS: %i", level.score()), text_x, text_y, 64, WHITE);
        DrawFPS(100, 100);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    delete level;
    return 0;
}