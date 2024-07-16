#define _USE_MATH_DEFINES
#include <objects.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <list>

//Too lazy to rename to circle
class Sphere : public Object {
public:
    int radius;
    double mass;
    bool magnetic;
    Sphere(){
        this->magnetic = false;
        this->radius = 1;
        this->mass = 0; //probably a bad idea
    }
    Sphere(double radius, double mass){
        this->radius = radius;
        this->mass = mass;
    }

    void Draw(SDL_Renderer *renderer){
        int sX = radius;
        int sY = 0;
        int tmp = 1 - radius;

        std::list<SDL_Point> points;

        SDL_Point p1 = {this->position.x + radius, this->position.y};
        SDL_Point p2 = {this->position.x, this->position.y + radius};
        SDL_Point p3 = {this->position.x, this->position.y - radius};
        SDL_Point p4 = {this->position.x - radius, this->position.y};

        points.push_front(p1);
        points.push_front(p2);
        points.push_front(p3);
        points.push_front(p4);

        while(sX > sY){
            sY++;

            if(tmp <= 0){
                tmp += 2*sY + 1;
            }
            else {
                sX--;
                tmp += 2*sY - 2*sX + 1;
            }

            if(sX < sY){
                break;
            }

            p1 = {sX + this->position.x, sY + this->position.y};
            p2 = {-sX + this->position.x, sY + this->position.y};
            p3 = {sX + this->position.x, -sY + this->position.y};
            p4 = {-sX + this->position.x, -sY + this->position.y};

            points.push_front(p1);
            points.push_front(p2);
            points.push_front(p3);
            points.push_front(p4);

            p1 = {sY + this->position.x, sX + this->position.y};
            p2 = {-sY + this->position.x, sX + this->position.y};
            p3 = {sY + this->position.x, -sX + this->position.y};
            p4 = {-sY + this->position.x, -sX + this->position.y};

            points.push_front(p1);
            points.push_front(p2);
            points.push_front(p3);
            points.push_front(p4);
        }

        int l = points.size();
        int k = 0;

        SDL_Point *p = (SDL_Point*)malloc(sizeof(SDL_Point) * l);

        for(auto const& i : points){
            p[k].x = i.x;
            p[k++].y = i.y;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoints(renderer, p, l + 1);
        free(p);
    }
};