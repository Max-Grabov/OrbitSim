#include "Object.hpp"

namespace OrbitSim
{
Object::Object(const int &x, const int &y, const int &z) : position_({x, y, z}), velocity_({0, 0, 0}), acceleration_({0, 0, 0}) {}

Object::Object(Vector position) : position_(std::move(position)), velocity_({0, 0, 0}), acceleration_({0, 0, 0}) {}

Object::Object(Vector position, VectorD velocity, VectorD acceleration)
    : position_(std::move(position)), velocity_(std::move(velocity)),
      acceleration_(std::move(acceleration))
{
}

void Object::setVelocity(VectorD velocity) { velocity_ = std::move(velocity); }

double Object::distance(const Object &A, const Object &B)
{
  return sqrt(pow(A.position_.x_ - B.position_.x_, 2) + pow(A.position_.y_ - B.position_.y_, 2));
}
} // namespace OrbitSim
