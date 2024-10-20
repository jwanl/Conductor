#pragma once

#include <memory>
#include "raylib.h"
#include <string>
#include "graphics.h"
#include "highscore.h"

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
        "../resources/rwbk.mp3",
        "../resources/music.mp3",
        "../resources/rick.mp3"
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
    std::vector<std::string> menu_items = {
        "play",
        "quit"
    };
};