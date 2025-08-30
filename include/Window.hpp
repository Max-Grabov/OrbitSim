#pragma once

#include <SDL2/SDL.h>

// TODO move renderer and text_renderer to members
namespace OrbitSim {
class Window {
  virtual void init(SDL_Renderer *renderer, const TextRenderer &text_renderer) = 0;

  virtual void exit(SDL_Renderer *renderer) = 0;

  virtual void run(SDL_Renderer *renderer, const TextRenderer &text_renderer, const Uint8 *keystate) = 0;
};
} // namespace OrbitSim
