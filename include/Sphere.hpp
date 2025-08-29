#pragma once
#include "SDL.h"
#include "Object.h"
#include "Init.h"

#include <cmath>
#include <list>

//Used to not add points that are in the hotbar space on the window
#define HOTBAR_H 100

class Sphere : public Object {
public:
    int radius_;
    double mass_;

    Sphere();

    Sphere(const double &radius = 1, const double &mass = 0);

    void Draw(SDL_Renderer *renderer, const int &offsetX, const int &offsetY) const;
};
#endif