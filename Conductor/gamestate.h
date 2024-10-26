#pragma once

#include <memory>
#include "raylib.h"
#include "main.h"
#include <string>
#include "graphics.h"
#include "highscore.h"

#ifdef PLATFORM_WEB
    #define MENU_ITEMS { "play" }
#else
    #define MENU_ITEMS { "play", "quit" }
#endif

class GameState {
public:
    virtual ~GameState() {}

    virtual std::unique_ptr<GameState> update() = 0;
    virtual void draw() = 0;

    bool should_close() const;

protected:
    static bool m_should_close;
};

class WinScreen : public GameState {
public:
    WinScreen(int levelId, int score);

    // Inherited via GameState
    std::unique_ptr<GameState> update() override;
    void draw() override;
private:
    int m_levelId;
    int m_score;
    float m_winMsgLeft;
    bool m_is_high_score;
};

class LevelState : public GameState {
public:
    LevelState(const char* audio_file, int levelId);

    ~LevelState();

    // Inherited via GameState
    std::unique_ptr<GameState> update() override;
    void draw() override;
private:
    Level* m_level;
    Camera camera;
    int levelId;
    float m_tooltipTimer = 3.0f;
};

class LevelSelector : public GameState {
public:
    // Inherited via GameState
    std::unique_ptr<GameState> update() override;
    void draw() override;
private:
    float space_pressed = 0.0f;
    int selected = 0;
    const char* levels[3] = {
        "level 1",
        "level 2",
        "level 3",
    };
    const char* musics[3] = {
        RES("rwbk.mp3"),
        RES("bizet.mp3"),
        RES("wagner.mp3"),
    };
    float is_released = false;
};

class MainMenu : public GameState {
public:
    std::unique_ptr<GameState> update() override;
    void draw() override;
private:
    int selected = 0;
    float space_pressed = 0.0f;
    std::vector<std::string> menu_items = MENU_ITEMS;
};
