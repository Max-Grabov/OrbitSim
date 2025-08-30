#pragma once

#include "Init.hpp"
#include "Object.hpp"

#include <cmath>
#include <list>

// Used to not add points that are in the hotbar space on the window
#define HOTBAR_H 100

namespace OrbitSim
{
class Sphere : public Object
{
public:
  int radius_;
  double mass_;

  Sphere(const double &radius = 1, const double &mass = 0);

  void Draw(SDL_Renderer *renderer, const int &offsetX, const int &offsetY) const;
};
} // namespace OrbitSim
