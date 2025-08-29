#include "Sphere.hpp"

Sphere::Sphere(const double &radius, const double &mass) : radius_(radius), mass_(mass) {}

void Sphere::Draw(SDL_Renderer *renderer, const int &offsetX, const int &offsetY) const
{
    int sX = radius;
    int sY = 0;
    int tmp = 1 - radius;

    std::list<SDL_Point> points;

    SDL_Point p1 = {position_.x_ + offsetX + radius, -position_.y_ + offsetY};
    SDL_Point p2 = {position_.x_ + offsetX, position_.y_ + offsetY + radius};
    SDL_Point p3 = {position_.x_ + offsetX, -position_.y_ + offsetY - radius};
    SDL_Point p4 = {position_.x_ + offsetX - radius, -position_.y_ + offsetY};

    if(-position_.y_ + offsetY >= HOTBAR_H){
        points.push_front(p1);
        points.push_front(p4);
    }

    if(-position_.y_ + offsetY + radius >= HOTBAR_H){
        points.push_front(p2);
    }

    if(-position_.y_ + offsetY - radius >= HOTBAR_H){
        points.push_front(p3);
    }

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

        p1 = {sX + position_.x_ + offsetX, sY + -position_.y_ + offsetY};
        p2 = {-sX + position_.x_ + offsetX, sY + -position_.y_ + offsetY};
        p3 = {sX + position_.x_ + offsetX, -sY + -position_.y_ + offsetY};
        p4 = {-sX + position_.x_ + offsetX, -sY + -position_.y_ + offsetY};

        if(sY + -position_.y_ + offsetY >= HOTBAR_H){
            points.push_front(p1);
            points.push_front(p2);
        }

        if(-sY + -position_.y_ + offsetY >= HOTBAR_H){
            points.push_front(p3);
            points.push_front(p4);
        }


        p1 = {sY + position_.x_ + offsetX, sX + -position_.y_ + offsetY};
        p2 = {-sY + position_.x_ + offsetX, sX + -position_.y_ + offsetY};
        p3 = {sY + position_.x_ + offsetX, -sX + -position_.y_ + offsetY};
        p4 = {-sY + position_.x_ + offsetX, -sX + -position_.y_ + offsetY};

        if(sX + -position_.y_ + offsetY >= HOTBAR_H){
            points.push_front(p1);
            points.push_front(p2);
        }

        if(-sX + -position_.y_ + offsetY >= HOTBAR_H){
            points.push_front(p3);
            points.push_front(p4);
        }

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
