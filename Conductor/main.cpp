#include "raylib.h"
#include "main.h"

#include "graphics.h"


#include <memory>
#include <iostream>
#include "level.h"

#include "gamestate.h"



int main(void)
{
    SetTraceLogLevel(LOG_TRACE);
    //GameState state = GameState::MainMenu;

    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    InitWindow(screenWidth, screenHeight, "Super Conductor Bros");

    SetTargetFPS(30);               // Set our game to run at 60 frames-per-second

    InitAudioDevice();


    
    Graphics::init(RES("background.png"),
        {RES("conductor_0.png"), RES("conductor_1.png"), RES("conductor_2.png")});


    std::unique_ptr<GameState> state = std::make_unique<MainMenu>();
    //std::unique_ptr<GameState> state = std::make_unique<LevelState>("../resources/music.mp3", 1);

    while (!WindowShouldClose() && !state->should_close()) {
        if (IsKeyPressed(KEY_TAB)) ToggleFullscreen();
        auto next_state = state->update();
       

        if (next_state) {
             state = std::move(next_state);
        }
        else {
            state->draw();
        }

    }

    

    CloseAudioDevice();

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}