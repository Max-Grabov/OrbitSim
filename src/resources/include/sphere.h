#ifndef _SPHERE_
#define _SPHERE_

#define _USE_MATH_DEFINES
#include "../SDL2/SDL.h"
#include "objects.h"
#include "init.h"
#include <math.h>
#include <list>

//Used to not add points that are in the hotbar space on the window
#define HOTBAR_H 100

//Too lazy to rename to circle
class Sphere : public Object {
public:
    int radius;
    double mass;
    bool magnetic;

    Sphere();

    Sphere(double radius, double mass);

    void Draw(SDL_Renderer *renderer, int offsetX, int offsetY);
};
#endif