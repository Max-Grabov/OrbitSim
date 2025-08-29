#pragma once

#include "Init.hpp"
#include "TextRenderer.hpp"

namespace OrbitSim
{
class Menu {
public:
    static void loadMenu(SDL_Renderer *renderer, const TextRenderer &text_renderer);
};
}
