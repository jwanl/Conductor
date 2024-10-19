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
    SetTraceLogLevel(LOG_TRACE);
    GameState state = GameState::MainMenu;

    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Super Conductor Bros");

    SetTargetFPS(240);               // Set our game to run at 60 frames-per-second

    InitAudioDevice();

    const char* level_musics[] = {
        "../resources/rwbk.mp3",
        "../resources/music.wav",
    };
    //const char* music = "../resources/rwbk.mp3";
    
    MusicPlayer menuplayer("../resources/rick.wav", 2.0f, 0.01f, 5.0f);
    

    menuplayer.play();
    menuplayer.set_volume(0.05f);

    Level* level = nullptr;

    int level_selected = 0;
    float time_out = 8.0f;
    float start_time = GetTime();
    

    Camera camera = { 0 };
    camera.position = { -3.0f, 0.0f, 0.0f };    // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    Graphics::init("../resources/background.png", 
        {"../resources/conductor_0.png", "../resources/conductor_1.png", "../resources/conductor_2.png"});

    float t0 = GetTime();
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_TAB)) {
            ToggleFullscreen();
        }
        
        switch (state) {
        case GameState::MainMenu: {
            BeginDrawing();

            const auto t = GetTime();
            if ((t - t0) > 8.0f) {
                t0 = t;
                menuplayer.start_effect();
            }

            menuplayer.update();

            Color col;
            col.g = 255.0f * (std::sin(GetTime() * 1.3f) * 0.5f + 0.5f);
            col.b = 255.0f * (std::sin(GetTime() * 0.8f) * 0.5f + 0.5f);
            col.r = 255.0f * (std::sin(GetTime() * 0.31f) * 0.5f + 0.5f);
            col.a = 255;


            const char* title = "Super Conductor!";
            const char* select_level = "Select level";
            const char* levels[] = {
                "level 1",
                "level 2",
                //"level 3",
            };
            

            ClearBackground(BLACK);
            auto w = MeasureText(title, 128);
            DrawText(title, GetScreenWidth() / 2.0f - w / 2.0f, 50, 128, col);


            auto f = 64 + std::sin(GetTime() * 1.0f) * 1;
            auto vec = MeasureTextEx(GetFontDefault(),select_level, f, 1.0f);

            time_out = 8.0f - GetTime() - start_time;

            DrawTextEx(GetFontDefault(), TextFormat("%s (%is)",select_level, (int)time_out), {GetScreenWidth() / 2.0f - vec.x / 2.0f, 320.0f}, f, 1.0f, col);

            for (int i = 0; i < 2; i++) {
                auto f = 64 + std::sin(GetTime() * 1.0f) * 1;
                if (i == level_selected) {
                    f = 92;

                }
                auto vec = MeasureTextEx(GetFontDefault(), levels[i], f, 1.0f);
                DrawTextEx(GetFontDefault(), levels[i], {GetScreenWidth() / 2.0f - vec.x / 2.0f, 400.0f + i * 80}, f, 1.0f, col);
            }

            if (IsKeyPressed(KEY_SPACE)) {
                level_selected = (level_selected + 1) % 2;
            }

            if (time_out < 0.0f) {
                state = GameState::Level;
                level = new Level(level_musics[level_selected]);
                level->play();
                menuplayer.stop();
            }

          

            EndDrawing();
        }break;
        case GameState::Level: {
            level->update();

            if (level->isOver()) {
                // Win screen here
            }

            // Pre-draw: Render to texture
            BeginTextureMode(Graphics::getTrackRenderTexture());
            Graphics::drawRenderTexture(level->getTrack());
            Graphics::drawHitLine(*level);
            EndTextureMode();


            // Draw
            BeginDrawing();

            ClearBackground(BLACK);

            Graphics::drawBackground();

            BeginMode3D(camera);
            Graphics::renderTrack();
            EndMode3D();

            Graphics::drawConductor(*level);

            const auto text_x = GetScreenWidth() * 0.7;
            const auto text_y = GetScreenHeight() * 0.0f;
            DrawText(TextFormat("POINTS: %i", level->score()), text_x, text_y, 64,WHITE);
            DrawFPS(0, 0);

            EndDrawing();
        }break;
        case GameState::WinScreen: {

            BeginDrawing();
            ClearBackground(BLACK);
            
            const auto text_x = GetScreenWidth() * 0.5f - 6 * 36;
            const auto text_y = GetScreenHeight() * 0.5f;
            const std::string winMessage = "SCORE: 5000";
            DrawText(winMessage.c_str(), text_x, text_y, 64, WHITE);

            EndDrawing();

        }break;
        }

    }

    delete level;
    menuplayer.unload();

    CloseAudioDevice();

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}