#include "include/Menu.hpp"

void Menu::loadMenu(SDL_Renderer *renderer, TextRenderer *tRenderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawRect(renderer, &Options[0]);
    tRenderer->render(renderer, "One Body", SCREEN_WIDTH/2 - 45 - 150, SCREEN_HEIGHT/2 - 50);
    tRenderer->render(renderer, "Simulation", SCREEN_WIDTH/2 - 43 - 150, SCREEN_HEIGHT/2 - 25);

    SDL_RenderDrawRect(renderer, &Options[1]);
    tRenderer->render(renderer, "Two Body", SCREEN_WIDTH/2 - 45 + 150, SCREEN_HEIGHT/2 - 50);
    tRenderer->render(renderer, "Simulation", SCREEN_WIDTH/2 - 43 + 150, SCREEN_HEIGHT/2 - 25);
}