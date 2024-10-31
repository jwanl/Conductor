#include "main.h"

#include <iostream>
#include <memory>

#include "gamestate.h"
#include "graphics.h"
#include "level.h"
#include "raylib.h"

#if 1
int main() { std::cout << "Hello\n"; }
#else

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

std::unique_ptr<GameState> state;

void updateDrawFrame() {
  if (IsKeyPressed(KEY_TAB)) ToggleFullscreen();
  auto next_state = state->update();

  if (next_state) {
    state = std::move(next_state);
  } else {
    state->draw();
  }
}

int main(void) {
  SetTraceLogLevel(LOG_TRACE);
  // GameState state = GameState::MainMenu;

  // Initialization
  const int screenWidth = 1280;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "Super Conductor Bros");

  InitAudioDevice();

  Graphics::init(
      RES("background.png"),
      {RES("conductor_0.png"), RES("conductor_1.png"), RES("conductor_2.png")});

  state = std::make_unique<MainMenu>();
  // std::unique_ptr<GameState> state = std::make_unique<MainMenu>();
  // std::unique_ptr<GameState> state =
  // std::make_unique<LevelState>("../resources/music.mp3", 1);

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(updateDrawFrame, 0, 1);
#else
  SetTargetFPS(30);  // Set our game to run at 60 frames-per-second

  while (!WindowShouldClose() && !state->should_close()) {
    updateDrawFrame();
  }
#endif

  CloseAudioDevice();

  // De-Initialization
  CloseWindow();  // Close window and OpenGL context

  return 0;
}

#endif