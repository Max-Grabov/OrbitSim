#ifndef MENU_H
#define MENU_H

#include <../SDL2/SDL.h>
#include <init.h>
#include <textRenderer.h>

class Menu {
public:
    static void loadMenu(SDL_Renderer *renderer, TextRenderer *tRenderer);
};

#endif