#include "gamestate.h"

void DrawCenteredText(std::string text, float size, Color color, float y) {
    //auto f = 64 + std::sin(GetTime() * 1.0f) * 1;
    auto vec = MeasureTextEx(GetFontDefault(), text.c_str(), size, 4.0f);

    //time_out -= GetFrameTime();

    DrawTextEx(GetFontDefault(), text.c_str(), { GetScreenWidth() / 2.0f - vec.x / 2.0f, y }, size, 4.0f, color);
}

bool GameState::should_close() const {
    return m_should_close;
}

bool GameState::m_should_close = false;

/* WIN SCREEN */

WinScreen::WinScreen(int levelId, int score) {
    m_levelId = levelId;
    m_score = score;
    m_winMsgLeft = 8.0f;
}

// Inherited via GameState
std::unique_ptr<GameState> WinScreen::update()
{
    m_winMsgLeft -= GetFrameTime();
    if (m_winMsgLeft <= 0.0f) {
        return std::make_unique<MainMenu>();
    }
    else return nullptr;
}
void WinScreen::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    const auto text_x = GetScreenWidth() * 0.5f - 6 * 36;
    const auto text_y = GetScreenHeight() * 0.5f;
    DrawText(TextFormat("You scored %i points", m_score), text_x, text_y, 64, YELLOW);

    EndDrawing();
}

/* LEVEL STATE */

LevelState::LevelState(const char* audio_file, int levelId) : m_level(new Level(audio_file, 10)), levelId(levelId) {
    camera.position = { -3.0f, 0.0f, 0.0f };    // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    m_level->play();
}

LevelState::~LevelState() {
    delete m_level;
}

// Inherited via GameState
std::unique_ptr<GameState> LevelState::update()
{
    m_level->update();

    if (m_level->isOver()) {
        // Win screen here
        int score = m_level->score();
        return std::make_unique<WinScreen>(levelId, score);
    }
    else return nullptr;
}

void LevelState::draw()
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
    DrawText(TextFormat("POINTS: %i", m_level->score()), text_x, text_y, 64, WHITE);
    DrawFPS(0, 0);

    EndDrawing();
}

    // Inherited via GameState
std::unique_ptr<GameState> LevelSelector::update()
{
      if (!is_released) {
        if (IsKeyReleased(KEY_SPACE)) {
            is_released = true;
        }
        return nullptr;
    }
    if (space_pressed > 1.0f) {

        return std::make_unique<LevelState>(musics[selected], selected);
    }
    else if (space_pressed < 0.5f && space_pressed > 0.1f && !IsKeyDown(KEY_SPACE)) {

        selected = (selected + 1) % 3;
        space_pressed = 0;
    }


    if (IsKeyDown(KEY_SPACE)) {
        space_pressed += GetFrameTime();
    }
    return nullptr;
}

void LevelSelector::draw()
{
    BeginDrawing();

    Color color;
    color.g = 255.0f * (std::sin(GetTime() * 1.3f) * 0.5f + 0.5f);
    color.b = 255.0f * (std::sin(GetTime() * 0.8f) * 0.5f + 0.5f);
    color.r = 255.0f * (std::sin(GetTime() * 0.31f) * 0.5f + 0.5f);
    color.a = 255;

    ClearBackground(BLACK);
    DrawCenteredText("Super Conductor!", 128, color, 50);

    for (int i = 0; i < 3; i++) {
        auto font_size = 64 + std::sin(GetTime() * 1.0f) * 1;
        if (i == selected) {
            font_size = 92;
        }
        DrawCenteredText(levels[i], font_size, color, 240 + i * 100);

    }
    EndDrawing();
}


std::unique_ptr<GameState> MainMenu::update() {
    if (space_pressed > 1.0f) {
        if (selected == 0) {
            return std::make_unique<LevelSelector>();
        }
        else if (selected == 1) {
            m_should_close = true;
        }

    }
    else if (space_pressed < 0.5f && space_pressed > 0.1f && !IsKeyDown(KEY_SPACE)) {

        selected = (selected + 1) % menu_items.size();
        space_pressed = 0;
    }



    if (IsKeyDown(KEY_SPACE)) {
        space_pressed += GetFrameTime();
    }

    return nullptr;
}

void MainMenu::draw() {
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