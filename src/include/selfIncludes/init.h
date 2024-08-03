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

const int w = 1300, h = 800;
const int offsetX = w/2;
const int offsetY = h/2 + 200;
const int hotbarH = 100;
const double frame = 0.01;

//X Y W H
SDL_Rect Screen = {0, hotbarH + 1, 2*w, h};

SDL_Rect Hotbar = {0, 0, 2*w, hotbarH};

SDL_Rect oneInputMass = {30, 20, 100, 19};

SDL_Rect twoInputMass = {30, 50, 100, 19};

void update(Sphere*, Sphere*, SDL_Renderer*, TextRenderer*, std::vector<TextInput*>, int, int);

void initHotbar(SDL_Renderer*, TextRenderer*, std::vector<TextInput*>);

#endif