//Holds constant values and static SDL_Rect/Surfaces to not clog up main
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#ifndef INIT_H_
#define INIT_H_

#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 800
#define OFFSET_X SCREEN_WIDTH/2
#define OFFSET_Y SCREEN_HEIGHT/2 + 200
#define HOTBAR_H 100
#define FRAME 0.01
#define SCREENS 2
#define BIG_MASS 2000000000000000000
#define SMALL_MASS 2000000000000

//X Y W H
SDL_Rect Screen = {0, HOTBAR_H + 1, 2*SCREEN_WIDTH, SCREEN_HEIGHT};

SDL_Rect Options [] = {{SCREEN_WIDTH/2 - 100 - 150, SCREEN_HEIGHT/2 - 100, 200, 200},
                       {SCREEN_WIDTH/2 - 100 + 150, SCREEN_HEIGHT/2 - 100, 200, 200}};


SDL_Rect Hotbar = {0, 0, 2*SCREEN_WIDTH, HOTBAR_H};

SDL_Rect oneInputMass = {139, 19, 100, 19};

SDL_Rect twoInputMass = {139, 59, 100, 19};

SDL_Rect oneInputVel = {433, 19, 100, 19};

SDL_Rect twoInputVel = {433, 59, 100, 19};

#endif