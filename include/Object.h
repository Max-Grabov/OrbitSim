#pragma once

#include <math.h>

#define G 6.67430e-11
#define gn = 9.80665

typedef struct Vector 
{
    int x_, y_, z_;
} Vector;

typedef struct VectorD 
{
    double x_, y_, z_;
} VectorD;

class Object 
{
private:
    Vector position_;
    VectorD velocity_;
    VectorD acceleration_;

public:
    Object(const int &x = 0, const int &y = 0, const int &z = 0);
   
    Object(const Vector &position);

    Object(const Vector &position, const VectorD &velocity, const VectorD &acceleration);

    inline Vector getPosition() const { return position_; }

    inline VectorD getVelocity() const { return velocity_; }

    inline VectorD getAcceleration() const { return acceleration_; }
    
    void setVelocity(const VectorD &velocity);

    void setVelocity(VectorD &&velocity)

    static double distance(const Object &obj1, const Object &obj2);
};