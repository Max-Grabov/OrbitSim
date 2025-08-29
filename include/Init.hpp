// Holds constant values and static SDL_Rect/Surfaces to not clog up main
#pragma once
#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 800
#define OFFSET_X SCREEN_WIDTH / 2
#define OFFSET_Y SCREEN_HEIGHT / 2 + 200
#define HOTBAR_H 100
#define FRAME 0.0075
#define SCREENS 3
#define BIG_MASS 2000000000000000000
#define SMALL_MASS 2000000000000
#define PIXELCONVERT 1
#define MOON_MASS 7.346e22 / 30
#define EARTH_MASS 5.9722e24 / 30
#define CONVERSION 63.78
#define INIT_DISTANCE 12833.333

// X Y W H
extern SDL_Rect Screen;

extern SDL_Rect Options[];

extern SDL_Rect Hotbar;

extern SDL_Rect oneInputMass;

extern SDL_Rect twoInputMass;

extern SDL_Rect oneInputVel;

extern SDL_Rect twoInputVel;

extern SDL_Rect threeInputVel;

extern SDL_Rect fourInputVel;
