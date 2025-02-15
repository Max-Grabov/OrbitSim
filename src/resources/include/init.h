//Holds constant values and static SDL_Rect/Surfaces to not clog up main
#include <iostream>
#include <vector>
#include <../SDL2/SDL.h>

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
extern SDL_Rect Screen;

extern SDL_Rect Options [];

extern SDL_Rect Hotbar;

extern SDL_Rect oneInputMass;

extern SDL_Rect twoInputMass;

extern SDL_Rect oneInputVel;

extern SDL_Rect twoInputVel;

#endif