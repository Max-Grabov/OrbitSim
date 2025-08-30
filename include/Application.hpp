#pragma once

#include "OneBody.hpp"
#include <cstdint>

namespace OrbitSim
{
class Application
{
public:
  void init();

  void run();

  void exit();
private:
  OneBody one_body_;
  TextRenderer text_renderer_;

  SDL_Renderer *renderer_{nullptr};
  SDL_Window *window_{nullptr};
  SDL_Event event_;
  const uint8_t *keystate_{nullptr};
  uint8_t selected_screen_;
  bool running_{false};

  void handleEvents();

  void handleKeyboardInput();

  void handleWindowChange();
};
}