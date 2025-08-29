#pragma once

#include "SDL2/SDL.h"
#include "Init.hpp"
#include "TextRenderer.hpp"

class Menu {
public:
    static void loadMenu(SDL_Renderer *renderer, TextRenderer *tRenderer);
};