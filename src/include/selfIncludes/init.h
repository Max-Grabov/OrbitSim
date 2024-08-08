//Holds constant values and static SDL_Rect/Surfaces to not clog up main
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SelfIncludes/sphere.h>
#include <SelfIncludes/textRenderer.h>
#include <SelfIncludes/objects.h>
#include <selfIncludes/textInput.h>

#ifndef INIT_H_
#define INIT_H_

#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 800
#define OFFSET_X SCREEN_WIDTH/2
#define OFFSET_Y SCREEN_HEIGHT/2 + 200
#define HOTBAR_H 100
#define FRAME 0.01

//X Y W H
SDL_Rect Screen = {0, HOTBAR_H + 1, 2*SCREEN_WIDTH, SCREEN_HEIGHT};

SDL_Rect Hotbar = {0, 0, 2*SCREEN_WIDTH, HOTBAR_H};

SDL_Rect oneInputMass = {100, 20, 100, 19};

SDL_Rect twoInputMass = {100, 60, 100, 19};

SDL_Rect oneInputVel = {327, 20, 100, 19};

SDL_Rect twoInputVel = {327, 60, 100, 19};

void update(Sphere*, Sphere*, SDL_Renderer*, TextRenderer*, std::vector<TextInput*>, int, int);

void initHotbar(SDL_Renderer*, TextRenderer*, std::vector<TextInput*>);

std::vector<TextInput*> initTextBox();

#endif