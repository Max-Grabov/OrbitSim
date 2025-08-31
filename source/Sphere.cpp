#include "Sphere.hpp"
#include <SDL2/SDL_rect.h>
#include <algorithm>
#include <cmath>
#include <utility>

namespace OrbitSim
{
Sphere::Sphere(const double &radius, const double &mass) : radius_(radius), mass_(mass)
{
  points_ = new SDL_Point[6 * radius_]();
}

Sphere::~Sphere() { delete[] points_; }

Sphere::Sphere(Sphere &&other) : radius_(std::move(other.radius_)), mass_(std::move(other.mass_))
{
  points_ = other.points_;
  other.points_ = nullptr;
}

Sphere &Sphere::operator=(Sphere &&other)
{
  radius_ = std::move(other.radius_);
  mass_ = std::move(other.mass_);

  points_ = other.points_;
  other.points_ = nullptr;

  return *this;
}

Sphere::Sphere(const Sphere &other) : radius_(other.radius_), mass_(other.mass_)
{

  if(!other.points_)
  {
    points_ = nullptr;
    return;
  }

  delete[] points_;

  points_ = new SDL_Point[6 * other.radius_]();

  for(size_t i = 0; i < other.radius_ * 6; ++i)
  {
    points_[i] = other.points_[i];
  }
}

Sphere &Sphere::operator=(const Sphere &other)
{
  radius_ = other.radius_;
  mass_ = other.mass_;

  if(!other.points_)
  {
    points_ = nullptr;
    return *this;
  }

  delete[] points_;

  points_ = new SDL_Point[6 * other.radius_]();

  for(size_t i = 0; i < other.radius_ * 6; ++i)
  {
    points_[i] = other.points_[i];
  }

  return *this;
}

void Sphere::Draw(SDL_Renderer *renderer, const int &camera_offset_x,
                  const int &camera_offset_y) const
{
  size_t counter{0};

  int sX = radius_;
  int sY = 0;
  int tmp = 1 - radius_;

  // Add the 4 points on the NESW of the Sphere
  if(-position_.y_ + camera_offset_y >= HOTBAR_H)
  {
    points_[counter].x = position_.x_ + camera_offset_x + radius_;
    points_[counter].y = -position_.y_ + camera_offset_y;

    ++counter;

    points_[counter].x = position_.x_ + camera_offset_x - radius_;
    points_[counter].y = -position_.y_ + camera_offset_y;

    ++counter;
  }

  if(-position_.y_ + camera_offset_y + radius_ >= HOTBAR_H)
  {
    points_[counter].x = position_.x_ + camera_offset_x;
    points_[counter].y = position_.y_ + camera_offset_y + radius_;

    ++counter;
  }

  if(-position_.y_ + camera_offset_y - radius_ >= HOTBAR_H)
  {
    points_[counter].x = position_.x_ + camera_offset_x;
    points_[counter].y = -position_.y_ + camera_offset_y - radius_;

    ++counter;
  }

  while(sX > sY)
  {
    sY++;

    if(tmp <= 0)
    {
      tmp += 2 * sY + 1;
    }
    else
    {
      sX--;
      tmp += 2 * sY - 2 * sX + 1;
    }

    if(sX < sY)
    {
      break;
    }

    if(sY + -position_.y_ + camera_offset_y >= HOTBAR_H)
    {
      points_[counter].x = sX + position_.x_ + camera_offset_x;
      points_[counter].y = sY - position_.y_ + camera_offset_y;

      ++counter;

      points_[counter].x = -sX + position_.x_ + camera_offset_x;
      points_[counter].y = sY - position_.y_ + camera_offset_y;

      ++counter;
    }

    if(-sY + -position_.y_ + camera_offset_y >= HOTBAR_H)
    {
      points_[counter].x = sX + position_.x_ + camera_offset_x;
      points_[counter].y = -sY - position_.y_ + camera_offset_y;

      ++counter;

      points_[counter].x = -sX + position_.x_ + camera_offset_x;
      points_[counter].y = -sY - position_.y_ + camera_offset_y;

      ++counter;
    }

    if(sX + -position_.y_ + camera_offset_y >= HOTBAR_H)
    {
      points_[counter].x = sY + position_.x_ + camera_offset_x;
      points_[counter].y = sX - position_.y_ + camera_offset_y;

      ++counter;

      points_[counter].x = -sY + position_.x_ + camera_offset_x;
      points_[counter].y = sX - position_.y_ + camera_offset_y;

      ++counter;
    }

    if(-sX + -position_.y_ + camera_offset_y >= HOTBAR_H)
    {
      points_[counter].x = sY + position_.x_ + camera_offset_x;
      points_[counter].y = -sX - position_.y_ + camera_offset_y;

      ++counter;

      points_[counter].x = -sY + position_.x_ + camera_offset_x;
      points_[counter].y = -sX - position_.y_ + camera_offset_y;

      ++counter;
    }
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoints(renderer, points_, counter + 1);
}
} // namespace OrbitSim
