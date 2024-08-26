#include <SDL2/SDL.h>
#include <SelfIncludes/init.h>
#include <SelfIncludes/textRenderer.h>

#ifndef _MENU_
#define _MENU_

class Menu {
public:
    static void loadMenu(SDL_Renderer *renderer, TextRenderer *tRenderer){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &oneBody);

        tRenderer->render(renderer, "One Body", SCREEN_WIDTH/2 - 45, SCREEN_HEIGHT/2 - 50);
        tRenderer->render(renderer, "Simulation", SCREEN_WIDTH/2 - 43, SCREEN_HEIGHT/2 - 25);
    }
};

#endif