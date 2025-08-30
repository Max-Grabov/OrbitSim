#include "Sphere.hpp"

namespace OrbitSim {
Sphere::Sphere(const double &radius, const double &mass) : radius_(radius), mass_(mass) {}

// TODO FIX THIS GARBAGE HOLY SHIT
void Sphere::Draw(SDL_Renderer *renderer, const int &camera_offset_x,
                  const int &camera_offset_y) const
{
  int sX = radius_;
  int sY = 0;
  int tmp = 1 - radius_;

  std::list<SDL_Point> points;

  SDL_Point p1 = {position_.x_ + camera_offset_x + radius_, -position_.y_ + camera_offset_y};
  SDL_Point p2 = {position_.x_ + camera_offset_x, position_.y_ + camera_offset_y + radius_};
  SDL_Point p3 = {position_.x_ + camera_offset_x, -position_.y_ + camera_offset_y - radius_};
  SDL_Point p4 = {position_.x_ + camera_offset_x - radius_, -position_.y_ + camera_offset_y};

  if (-position_.y_ + camera_offset_y >= HOTBAR_H) {
    points.push_front(p1);
    points.push_front(p4);
  }

  if (-position_.y_ + camera_offset_y + radius_ >= HOTBAR_H) {
    points.push_front(p2);
  }

  if (-position_.y_ + camera_offset_y - radius_ >= HOTBAR_H) {
    points.push_front(p3);
  }

  while (sX > sY) {
    sY++;

    if (tmp <= 0) {
      tmp += 2 * sY + 1;
    }
    else {
      sX--;
      tmp += 2 * sY - 2 * sX + 1;
    }

    if (sX < sY) {
      break;
    }

    p1 = {sX + position_.x_ + camera_offset_x, sY + -position_.y_ + camera_offset_y};
    p2 = {-sX + position_.x_ + camera_offset_x, sY + -position_.y_ + camera_offset_y};
    p3 = {sX + position_.x_ + camera_offset_x, -sY + -position_.y_ + camera_offset_y};
    p4 = {-sX + position_.x_ + camera_offset_x, -sY + -position_.y_ + camera_offset_y};

    if (sY + -position_.y_ + camera_offset_y >= HOTBAR_H) {
      points.push_front(p1);
      points.push_front(p2);
    }

    if (-sY + -position_.y_ + camera_offset_y >= HOTBAR_H) {
      points.push_front(p3);
      points.push_front(p4);
    }

    p1 = {sY + position_.x_ + camera_offset_x, sX + -position_.y_ + camera_offset_y};
    p2 = {-sY + position_.x_ + camera_offset_x, sX + -position_.y_ + camera_offset_y};
    p3 = {sY + position_.x_ + camera_offset_x, -sX + -position_.y_ + camera_offset_y};
    p4 = {-sY + position_.x_ + camera_offset_x, -sX + -position_.y_ + camera_offset_y};

    if (sX + -position_.y_ + camera_offset_y >= HOTBAR_H) {
      points.push_front(p1);
      points.push_front(p2);
    }

    if (-sX + -position_.y_ + camera_offset_y >= HOTBAR_H) {
      points.push_front(p3);
      points.push_front(p4);
    }
  }

  int l = points.size();
  int k = 0;

  SDL_Point *p = (SDL_Point *)malloc(sizeof(SDL_Point) * l);

  for (auto const &i : points) {
    p[k].x = i.x;
    p[k++].y = i.y;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoints(renderer, p, l + 1);
  free(p);
}
} // namespace OrbitSim
