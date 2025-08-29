#pragma once

#include "Init.hpp"
#include "Menu.hpp"
#include "Sphere.hpp"
#include "TextInput.hpp"
#include "TextRenderer.hpp"
#include "Window.hpp"

#include <array>

namespace OrbitSim {
class OneBody : public Window {
public:
  void init(SDL_Renderer *renderer) override;

  void reset() override;

  void run() override;

  static void calc(SDL_Renderer *renderer);

  static void initHotbar(SDL_Renderer *renderer);

  static void initTextBox();

  static int update(const char &input_char, const Uint8 *keyState, const SDL_Event &e,
                    SDL_Renderer *renderer, const TextRenderer &text_renderer);

private:
  Sphere sphere_one_, sphere_two_;
  int camera_offset_x_, camera_offset_y_;
  bool pause_;
  std::array<TextInput, 4> textboxes_;
  std::array<SDL_Rect, 4> textbox_borders_{
      {139, 19, 100, 19}, {139. 59, 100, 19}, {433, 19, 100, 19}, {433, 59, 100, 19}};
  int selected_box_;

  void InitHotbar(SDL_Renderer *renderer);
};
} // namespace OrbitSim
