#include <math.h>
#define G 0.000000000066741
#define gn = 9.80665

#ifndef _OBJECT_
#define _OBJECT_

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
    Object(){
        this->position = {0, 0, 0};
    }
    Object(vector position){
        this->position = position;
    }

    void setVelocity(vectord velocity){
        this->velocity = velocity;
    }

    void setAcceleration(vectord acceleration){
        this->acceleration = acceleration;
    }

    static double distance(Object obj1, Object obj2){
        return sqrt(pow(obj1.position.x - obj2.position.x, 2) + pow(obj1.position.y - obj2.position.y, 2));
    }
};
#endif