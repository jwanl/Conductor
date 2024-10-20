#include "raylib.h"
#include "main.h"

#include "graphics.h"


#include <memory>
#include <iostream>
#include "level.h"





void DrawCenteredText(std::string text, float size, Color color, float y) {
    //auto f = 64 + std::sin(GetTime() * 1.0f) * 1;
    auto vec = MeasureTextEx(GetFontDefault(), text.c_str(), size, 4.0f);

    //time_out -= GetFrameTime();

    DrawTextEx(GetFontDefault(), text.c_str(), { GetScreenWidth() / 2.0f - vec.x / 2.0f, y }, size, 4.0f, color);

}

class GameState {
public:
    virtual ~GameState() {}

    virtual std::unique_ptr<GameState> update() = 0;
    virtual void draw() = 0;

    bool should_close() const {
        return m_should_close;
    }

protected:
    static bool m_should_close;
};

bool GameState::m_should_close = false;

class WinScreen : public GameState {
public:
    WinScreen(int levelId, int score) {

    }

    // Inherited via GameState
    std::unique_ptr<GameState> update() override
    {
        return std::unique_ptr<GameState>();
    }
    void draw() override
    {
    }
};

class LevelState : public GameState {
public:
    LevelState(const char* audio_file, int levelId) : m_level(new Level(audio_file, 10)), levelId(levelId) {
        camera.position = { -3.0f, 0.0f, 0.0f };    // Camera position
        camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
        camera.up = { 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
        camera.fovy = 45.0f;                                // Camera field-of-view Y
        camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

        m_level->play();
    }

    ~LevelState() {
        delete m_level;
    }

    // Inherited via GameState
    std::unique_ptr<GameState> update() override
    {
        m_level->update();

        if (m_level->isOver()) {
            // Win screen here
            int score = m_level->score();
            return std::make_unique<WinScreen>(levelId, score);
        }
        else return nullptr;
    }

    void draw() override
    {
        


                // Pre-draw: Render to texture
                BeginTextureMode(Graphics::getTrackRenderTexture());
                Graphics::drawRenderTexture(m_level->getTrack());
                Graphics::drawHitLine(*m_level);
                EndTextureMode();


                // Draw
                BeginDrawing();

                ClearBackground(BLACK);

                Graphics::drawBackground();

                BeginMode3D(camera);
                Graphics::renderTrack();
                EndMode3D();

                Graphics::drawConductor(*m_level);
                Graphics::drawProgressBar(m_level->getPercentageDone());

                const auto text_x = GetScreenWidth() * 0.6;
                const auto text_y = GetScreenHeight() * 0.0f;
                DrawText(TextFormat("POINTS: %i", m_level->score()), text_x, text_y, 64,WHITE);
                DrawFPS(0, 0);

                EndDrawing();
    }


private:
    Level* m_level = nullptr;
    Camera camera;
    int levelId;

};

class LevelSelector : public GameState {
public:
    // Inherited via GameState
    std::unique_ptr<GameState> update() override
    {
        if (space_pressed > 1.0f) {
            
            return std::make_unique<LevelState>(musics[selected], selected);
        }
        else if (IsKeyReleased(KEY_SPACE)) {
            if (space_pressed < 0.5f) {
                selected = (selected + 1) % levels.size();
            }
            space_pressed = 0;
        }

        if (IsKeyDown(KEY_SPACE)) {
            space_pressed += GetFrameTime();
        }

       

        return nullptr;
    }

    void draw() override
    {
        BeginDrawing();

        Color color;
        color.g = 255.0f * (std::sin(GetTime() * 1.3f) * 0.5f + 0.5f);
        color.b = 255.0f * (std::sin(GetTime() * 0.8f) * 0.5f + 0.5f);
        color.r = 255.0f * (std::sin(GetTime() * 0.31f) * 0.5f + 0.5f);
        color.a = 255;

        ClearBackground(BLACK);
        DrawCenteredText("Super Conductor!", 128, color, 50);

        for (int i = 0; i < levels.size(); i++) {
            auto font_size = 64 + std::sin(GetTime() * 1.0f) * 1;
            if (i == selected) {
                font_size = 92;
            }
            DrawCenteredText(levels[i], font_size, color, 240 + i * 100);

        }
        EndDrawing();
    }

private:
    float space_pressed = 0.0f;
    int selected = 0;
    std::vector<std::string> levels = {
        "level 1",
        "level 2",
        "level 3",
    };

    const char* musics[3] = {
        "../resources/rwbk.mp3",
        "../resources/music.mp3",
        "../resources/rick.mp3"
    };
};

class MainMenu : public GameState {
public:
    std::unique_ptr<GameState> update() override {
        if (space_pressed > 1.5f) {
            if (selected == 0) {
                return std::make_unique<LevelSelector>();
            }
            else if (selected == 1) {
                m_should_close = true;
            }
           
        }
        else if (IsKeyReleased(KEY_SPACE)) {
            if (space_pressed < 0.5f) {
                selected = (selected + 1) % menu_items.size();
            }
            space_pressed = 0;
        }

        if (IsKeyDown(KEY_SPACE)) {
            space_pressed += GetFrameTime();
        }

        return nullptr;
    }

    void draw() override {
        BeginDrawing();

        Color color;
        color.g = 255.0f * (std::sin(GetTime() * 1.3f) * 0.5f + 0.5f);
        color.b = 255.0f * (std::sin(GetTime() * 0.8f) * 0.5f + 0.5f);
        color.r = 255.0f * (std::sin(GetTime() * 0.31f) * 0.5f + 0.5f);
        color.a = 255;

        ClearBackground(BLACK);
        DrawCenteredText("Super Conductor!", 128, color, 50);

        for (int i = 0; i < menu_items.size(); i++) {
            auto font_size = 64 + std::sin(GetTime() * 1.0f) * 1;
            if (i == selected) {
                font_size = 92;
            }
            DrawCenteredText(menu_items[i], font_size, color, 240 + i * 100);

        }
        EndDrawing();
    }
private:
    int selected = 0;
    float space_pressed = 0.0f;
    std::vector<std::string> menu_items = {
        "play",
        "quit"
    };
};



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
        state->draw();

        if (next_state) {
            state = std::move(next_state);
        }

    }

    //float t0 = GetTime();
    //// Main game loop
    //while (!WindowShouldClose())    // Detect window close button or ESC key
    //{
    //    if (IsKeyPressed(KEY_TAB)) {
    //        ToggleFullscreen();
    //    }
    //    // Update all timers
    //    //Timer::updateAll(GetFrameTime());
    //    
    //    switch (state) {
    //    case GameState::MainMenu: {
    //        BeginDrawing();

    //       /* const auto t = GetTime();
    //        if ((t - t0) > 8.0f) {
    //            t0 = t;
    //            menuplayer.start_effect();
    //        }

    //        menuplayer.update();*/

    //        Color col;
    //        col.g = 255.0f * (std::sin(GetTime() * 1.3f) * 0.5f + 0.5f);
    //        col.b = 255.0f * (std::sin(GetTime() * 0.8f) * 0.5f + 0.5f);
    //        col.r = 255.0f * (std::sin(GetTime() * 0.31f) * 0.5f + 0.5f);
    //        col.a = 255;


    //        /*const char* title = "Super Conductor!";
    //        const char* select_level = "Select level";
    //        const char* levels[] = {
    //            "level 1",
    //            "level 2",
    //            "level 3",
    //        };*/
    //        

    //        ClearBackground(BLACK);
    //        DrawCenteredText("Super Conductor!", 128, col, 50);

    //        
    //        

    //        std::vector<std::string> menu_items = {
    //            "play",
    //            "levels",
    //            "quit"
    //        };

    //        for (int i = 0; i < menu_items.size(); i++) {
    //            auto font_size = 64 + std::sin(GetTime() * 1.0f) * 1;
    //            if (i == level_selected) {
    //                font_size = 92;
    //            }
    //            DrawCenteredText(menu_items[i], font_size, col, 240 + i * 100);

    //        }

    //       


    //        //auto vec = MeasureTextEx(GetFontDefault(),select_level, f, 4.0f);

    //        //time_out -= GetFrameTime();

    //        //DrawTextEx(GetFontDefault(), TextFormat("%s (%is)",select_level, (int)time_out), {GetScreenWidth() / 2.0f - vec.x / 2.0f, 320.0f}, f, 4.0f, col);

    //        //for (int i = 0; i < 3; i++) {
    //        //    auto f = 64 + std::sin(GetTime() * 1.0f) * 1;
    //        //    if (i == level_selected) {
    //        //        f = 92;

    //        //    }
    //        //    auto vec = MeasureTextEx(GetFontDefault(), levels[i], f, 4.0f);
    //        //    DrawTextEx(GetFontDefault(), levels[i], {GetScreenWidth() / 2.0f - vec.x / 2.0f, 400.0f + i * 80}, f, 4.0f, col);
    //        //}

    //        //if (IsKeyPressed(KEY_SPACE)) {
    //        //    level_selected = (level_selected + 1) % 3;
    //        //}

    //        //if (time_out < 0.0f) {
    //        //    state = GameState::Level;
    //        //    level = new Level(level_musics[level_selected]);
    //        //    level->play();
    //        //    //menuplayer.stop();
    //        //}

    //      

    //        EndDrawing();
    //    }break;
    //    case GameState::Level: {
    //        level->update();


    //        // Pre-draw: Render to texture
    //        BeginTextureMode(Graphics::getTrackRenderTexture());
    //        Graphics::drawRenderTexture(level->getTrack());
    //        Graphics::drawHitLine(*level);
    //        EndTextureMode();


    //        // Draw
    //        BeginDrawing();

    //        ClearBackground(BLACK);

    //        Graphics::drawBackground();

    //        BeginMode3D(camera);
    //        Graphics::renderTrack();
    //        EndMode3D();

    //        Graphics::drawConductor(*level);

    //        const auto text_x = GetScreenWidth() * 0.6;
    //        const auto text_y = GetScreenHeight() * 0.0f;
    //        DrawText(TextFormat("POINTS: %i", level->score()), text_x, text_y, 64,WHITE);
    //        DrawFPS(0, 0);

    //        EndDrawing();

    //        if (level->isOver()) {
    //            // Win screen here
    //            lastScore = level->score();
    //            state = GameState::WinScreen;
    //            delete level;
    //        }
    //    }break;
    //    case GameState::WinScreen: {

    //        /*if (winTimer == nullptr) {
    //            winTimer = new Timer(5.0f);
    //        }

    //        if (winTimer->isDone()) {
    //            state = GameState::MainMenu;
    //            delete winTimer;
    //        }*/

    //        BeginDrawing();
    //        ClearBackground(BLACK);
    //        
    //        const auto text_x = GetScreenWidth() * 0.5f - 6 * 36;
    //        const auto text_y = GetScreenHeight() * 0.5f;
    //        DrawText(TextFormat("You scored %i points", lastScore), text_x, text_y, 64, YELLOW);

    //        EndDrawing();

    //        winMsgLeft -= GetFrameTime();
    //        if (winMsgLeft <= 0.0f) {
    //            state = GameState::MainMenu;
    //            winMsgLeft = winMsgTime;
    //            time_out = 8.0f;
    //        }

    //    }break;
    //    }

    //}

    //menuplayer.unload();

    CloseAudioDevice();

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}