#pragma once

#include <SDL2/SDL.h>

namespace OrbitSim {
class Window {
  virtual void init(SDL_Renderer *renderer, const TextRenderer &text_renderer) = 0;

  virtual void reset(SDL_Renderer *renderer) = 0;

  virtual void run(SDL_Renderer *renderer) = 0;
};
} // namespace OrbitSim
