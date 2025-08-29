#include "Object.h"

Object::Object(const int &x, const int &y, const int &z)
{
    position_ = {x, y, z};
}

void Object::setVelocity(VectorD &&velocity)
{
    velocity_ = std::move(velocity);
}

void Object::setVelocity(const VectorD &velocity)
{
    velocity_ = velocity;
}
double Object::distance(const Object &A, const Object &B)
{
    return sqrt(pow(A.position.x - B.position.x, 2) + pow(A.position.y - B.position.y, 2));
}