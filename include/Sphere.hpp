#pragma once

#include "Object.hpp"
#include <SDL2/SDL.h>

#include <cmath>

#define HOTBAR_H 100

namespace OrbitSim
{
class Sphere : public Object
{
public:
  Sphere(const double &radius = 1, const double &mass = 0);

  ~Sphere();

  Sphere(Sphere &&other);

  Sphere &operator=(Sphere &&other);

  Sphere(const Sphere &other);

  Sphere &operator=(const Sphere &other);

  const int &getRadius() const { return radius_; }

  const double &getMass() const { return mass_; }

  const SDL_Point *getPoints() const { return points_; }

  void setMass(const double &mass) { mass_ = mass; }

  void Draw(SDL_Renderer *renderer, const int &offsetX, const int &offsetY) const;

private:
  int radius_;
  double mass_;
  SDL_Point *points_{nullptr};
};
} // namespace OrbitSim
