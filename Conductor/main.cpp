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

    const char* level_musics[] = {
        "../resources/rwbk.wav",
        "../resources/music.mp3",
        "../resources/rick.mp3",
    };
    

    /*Level* level = nullptr;
    int lastScore = 0;

    int level_selected = 0;
    float time_out = 8.0f;

    float winMsgTime = 5.0f;
    float winMsgLeft = winMsgTime;*/

    

    
    Graphics::init("../resources/background.png", 
        {"../resources/conductor_0.png", "../resources/conductor_1.png", "../resources/conductor_2.png"});


    std::unique_ptr<GameState> state = std::make_unique<MainMenu>();

    while (!WindowShouldClose() && !state->should_close()) {
        
        auto next_state = state->update();
       

        if (next_state) {
             state = std::move(next_state);
        }
        else {
            state->draw();
        }

    }

    //

    CloseAudioDevice();

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}