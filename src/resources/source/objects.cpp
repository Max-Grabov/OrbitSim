#include "../include/objects.h"

Object::Object(){
    this->position = {0, 0, 0};
}

void Object::setVelocity(vectord v){
    this->velocity = v;
}

double Object::distance(Object obj1, Object obj2){
    return sqrt(pow(obj1.position.x - obj2.position.x, 2) + pow(obj1.position.y - obj2.position.y, 2));
}