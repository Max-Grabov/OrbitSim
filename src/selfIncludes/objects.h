#ifndef _OBJECT_
#define _OBJECT_
typedef struct vector {
    int x, y, z;
}vector;

class Object {
public:
    vector position;
    vector velocity;
    vector acceleration;
    Object(){
        this->position = {0, 0, 0};
    }
    Object(vector position){
        this->position = position;
    }

    void setVelocity(vector velocity){
        this->velocity = velocity;
    }

    void setAcceleration(vector acceleration){
        this->acceleration = acceleration;
    }
};
#endif