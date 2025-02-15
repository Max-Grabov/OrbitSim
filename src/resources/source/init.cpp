#include "../include/init.h"

SDL_Rect Screen = {0, HOTBAR_H + 1, 2*SCREEN_WIDTH, SCREEN_HEIGHT};

SDL_Rect Options [] = {{SCREEN_WIDTH/2 - 100 - 150, SCREEN_HEIGHT/2 - 100, 200, 200},
                       {SCREEN_WIDTH/2 - 100 + 150, SCREEN_HEIGHT/2 - 100, 200, 200}};


SDL_Rect Hotbar = {0, 0, 2*SCREEN_WIDTH, HOTBAR_H};

SDL_Rect oneInputMass = {139, 19, 100, 19};

SDL_Rect twoInputMass = {139, 59, 100, 19};

SDL_Rect oneInputVel = {433, 19, 100, 19};

SDL_Rect twoInputVel = {433, 59, 100, 19};