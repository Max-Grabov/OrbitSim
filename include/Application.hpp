#pragma once

#include "OneBody.hpp"
#include "TwoBody.hpp"
#include <cstdint>

namespace OrbitSim
{
class Application
{
public:
  Application();

  Application &operator=(const Application &other) = delete;

  Application(const Application &other) = delete;

  Application &operator=(const Application &&other) = delete;

  Application(const Application &&other) = delete;

  ~Application();

  void run();

private:
  OneBody one_body_;
  TwoBody two_body_;  

  SDL_Window *window_{nullptr};
  SDL_Renderer *renderer_{nullptr};
  TextRenderer text_renderer_;

  SDL_Event event_;
  const uint8_t *keystate_{nullptr};
  uint8_t selected_screen_;
  bool running_{false};

  void handleEvents();

  void handleKeyboardInput();

  void handleWindowChange();

  void renderMenu();
};
} // namespace OrbitSim
