#include "Menu.hpp"

namespace OrbitSim {
void Menu::loadMenu(SDL_Renderer *renderer, const TextRenderer &text_renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

  SDL_RenderDrawRect(renderer, &Options[0]);
  text_renderer.render(renderer, "One Body", SCREEN_WIDTH / 2 - 45 - 150, SCREEN_HEIGHT / 2 - 50);
  text_renderer.render(renderer, "Simulation", SCREEN_WIDTH / 2 - 43 - 150, SCREEN_HEIGHT / 2 - 25);

  SDL_RenderDrawRect(renderer, &Options[1]);
  text_renderer.render(renderer, "Two Body", SCREEN_WIDTH / 2 - 45 + 150, SCREEN_HEIGHT / 2 - 50);
  text_renderer.render(renderer, "Simulation", SCREEN_WIDTH / 2 - 43 + 150, SCREEN_HEIGHT / 2 - 25);
}
} // namespace OrbitSim
