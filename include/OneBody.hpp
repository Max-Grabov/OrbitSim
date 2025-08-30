#pragma once

#include "Init.hpp"
#include "Menu.hpp"
#include "Sphere.hpp"
#include "TextInput.hpp"
#include "TextRenderer.hpp"
#include "Window.hpp"

#include <array>

// TODO Clearly every method includes the renderer, once again reminder to make a fucking wrapper
// for it Also, make these windows have a text renderer (static maybe?) member since it is so
// commonly used
namespace OrbitSim {
class OneBody : public Window {
public:
  // TODO Pause should be moved back to private
  bool pause_{false};

  void init(SDL_Renderer *renderer, const TextRenderer &text_renderer) override;

  void reset(SDL_Renderer *renderer) override;

  void run(SDL_Renderer *renderer) override;

  // TODO both inits should be privatized in favor of using the base init method from the virtual
  // class
  // TODO Also calc needs to be privatized eventually
  // TODO Eventually turn Update into the run method
  void initHotbar(SDL_Renderer *renderer, const TextRenderer &text_renderer);

  void initData(SDL_Renderer *renderer);

  void calc(SDL_Renderer *renderer);

  int update(const Uint8 *key_state, const SDL_Event &event, SDL_Renderer *renderer,
             const TextRenderer &text_renderer);

private:
  Sphere sphere_one_, sphere_two_;
  int camera_offset_x_{0}, camera_offset_y_{0};
  std::array<TextInput, 4> textboxes_;
  std::array<SDL_Rect, 4> textbox_borders_{SPHERE_ONE_MASS_BORDER, SPHERE_TWO_MASS_BORDER,
                                           SPHERE_ONE_VELOCITY_X_BORDER,
                                           SPHERE_ONE_VELOCITY_Y_BORDER};
  int selected_box_{0};

  void InitHotbar(SDL_Renderer *renderer);
};
} // namespace OrbitSim
