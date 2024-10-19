#include "raylib.h"
#include "main.h"

#include "graphics.h"


#include <iostream>
#include "level.h"

enum class GameState {
    MainMenu,
    Level,
    WinScreen
};

int main(void)
{
    GameState state = GameState::MainMenu;

    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Super Conductor Bros");

    SetTargetFPS(30);               // Set our game to run at 60 frames-per-second

    InitAudioDevice();
    const char* music = "../resources/rwbk.wav";
    

    //ToggleFullscreen();
  

    Level* level = nullptr;

    

    Camera camera = { 0 };
    camera.position = { -3.0f, 0.0f, 0.0f };    // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    Graphics::init("../resources/background.png", 
        {"../resources/conductor_0.png", "../resources/conductor_1.png", "../resources/conductor_2.png"});

    //level->play();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        switch (state) {
        case GameState::MainMenu: {
            BeginDrawing();

            Color col;
            col.g = 255.0f * (std::sin(GetTime() * 2.3f) * 0.5f + 0.5f);
            col.b = 255.0f * (std::sin(GetTime() * 1.8f) * 0.5f + 0.5f);
            col.r = 255.0f * (std::sin(GetTime() * 1.31f) * 0.5f + 0.5f);
            col.a = 255;


            ClearBackground(BLACK);
            auto w = MeasureText("Super Conductor!", 128);
            DrawText("Super Conductor!", GetScreenWidth() / 2.0f - w / 2.0f, 50, 128, col);


            auto f = 64 + std::sin(GetTime() * 1.0f) * 1;
            auto vec = MeasureTextEx(GetFontDefault(),"Press the only button to start!", f, 1.0f);
            DrawTextEx(GetFontDefault(), "Press the only button to start!", { GetScreenWidth() / 2.0f - vec.x / 2.0f, 320.0f }, f, 1.0f, col);
            //DrawText("Press the only button to start!", GetScreenWidth() / 2.0f - w / 2.0f, 320, f, WHITE);

            if (IsKeyPressed(KEY_SPACE)) {
                state = GameState::Level;
                level = new Level(music);
                level->play();
            }

            EndDrawing();
        }break;
        case GameState::Level: {
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
            DrawText(TextFormat("POINTS: %i", level->score()), text_x, text_y, 64,WHITE);
            DrawFPS(100, 100);

            EndDrawing();
        }break;
        case GameState::WinScreen: {

        }break;
        }

        

        
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    delete level;
    return 0;
}