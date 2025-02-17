#ifndef _OBJECT_
#define _OBJECT_

#include <math.h>

#define G 6.67430e-11
#define gn = 9.80665

typedef struct vector {
    int x, y, z;
}vector;

typedef struct vectord {
    double x, y, z;
}vectord;

class Object {
public:
    vector position;
    vectord velocity;
    vectord acceleration;
    Object();

    void setVelocity(vectord v);

    static double distance(Object obj1, Object obj2);
};
#endif