#pragma once

#include "Init.hpp"
#include "Sphere.hpp"
#include "TextInput.hpp"
#include "TextRenderer.hpp"
#include "Window.hpp"

#include <array>

// TODO Clearly every method includes the renderer, once again reminder to make a fucking wrapper
// for it Also, make these windows have a text renderer (static maybe?) member since it is so
// commonly used
namespace OrbitSim
{
class TwoBody : public Window
{
public:
  void run(SDL_Renderer *renderer, const TextRenderer &text_renderer,
           const Uint8 *keystate) override;

  void init(SDL_Renderer *renderer, const TextRenderer &text_renderer) override;

  void exit(SDL_Renderer *renderer) override;

private:
  Sphere sphere_one_, sphere_two_;
  int camera_offset_x_{0}, camera_offset_y_{0};
  std::array<TextInput, 6> textboxes_;
  std::array<SDL_Rect, 6> textbox_borders_{
      SPHERE_ONE_MASS_BORDER,       SPHERE_TWO_MASS_BORDER,       SPHERE_ONE_VELOCITY_X_BORDER,
      SPHERE_ONE_VELOCITY_Y_BORDER, SPHERE_TWO_VELOCITY_X_BORDER, SPHERE_TWO_VELOCITY_Y_BORDER};
  int selected_box_{0};
  bool running_{false};
  SDL_Event current_event_;
  bool pause_{false};

  void handleEvents(const SDL_Event &event, SDL_Renderer *renderer,
                    const TextRenderer &text_renderer, const Uint8 *keystate);

  void handleKeyboardInput(const SDL_Event &event, SDL_Renderer *renderer,
                           const TextRenderer &text_renderer, const Uint8 *keystate);

  void initHotbar(SDL_Renderer *renderer, const TextRenderer &text_renderer);

  void initData(SDL_Renderer *renderer);

  void calc(SDL_Renderer *renderer);
};
} // namespace OrbitSim
