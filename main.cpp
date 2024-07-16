#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <objects.h>
#include <sphere.h>

const int w = 1200, h = 800;
const double frame = 0.1;

bool c = false;

Sphere *s1 = new Sphere(200, 2000000000000000000);
Sphere *s2 = new Sphere(20, 2000000000);

void update(Sphere *s1, Sphere *s2, SDL_Renderer *renderer);

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Touhou", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!window){
        std::cout << "Error creating window" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    bool on = true;
    SDL_Event event;

    while(on){
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                on = false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode){
                case SDL_SCANCODE_C:
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);
                    break;
                }
                case SDL_SCANCODE_I:
                {
                    s1->position.x = w/2;
                    s1->position.y = h/2;

                    s2->position.x = w/2 + 400;
                    s2->position.y = h/2 - 200;

                    s2->velocity.x = 100;
                    s2->velocity.y = 100;

                    s1->Draw(renderer);
                    s2->Draw(renderer);

                    c = true;

                    break;
                }

                case SDL_SCANCODE_S:
                {
                    Sphere *s = new Sphere(200, 0);

                    s->position.x = w/3;
                    s->position.y = h/3;

                    s->Draw(renderer);
                    break;
                }
                case SDL_SCANCODE_ESCAPE:
                {
                    on = false;
                    break;
                }

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }
        if(c){
            update(s1, s2, renderer);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

//So far one body problem (big sphere is immobile)
void update(Sphere *s1, Sphere *s2, SDL_Renderer *renderer){
    double rad = s1->distance(*s1, *s2) - s1->radius - s2->radius;

    double forceG = (G * s2->mass  * s1->mass)/(pow(rad, 2));
    double forceC = (s2->mass * sqrt(pow(s2->velocity.x, 2) + pow(s2->velocity.y, 2)))/(rad);

    double thetaG = (s2->position.x == s1->position.x) ?
                    (M_PI/2) :
                    abs(atan((s2->position.y - s1->position.y)/(s2->position.x - s1->position.x)));

    if(s2->position.x > s1->position.x && s2->position.y > s1->position.y){
        thetaG = thetaG;
    }
    else if(s2->position.x > s1->position.x && s2->position.y < s1->position.y){
        thetaG = -thetaG;
    }
    else if(s2->position.x < s1->position.x && s2->position.y > s1->position.y){
        thetaG = (M_PI - thetaG);
    }
    else if(s2->position.x < s1->position.x && s2->position.y < s1->position.y){
        thetaG = -(M_PI - thetaG);
    }
    else {
        thetaG = M_PI/2;
    }

    double FxG = -cos(thetaG) * forceG;
    double FyG = -sin(thetaG) * forceG;

    double FxC = sin(thetaG) * forceC;
    double FyC = cos(thetaG) * forceC;

    double FnX = FxG + FxC;
    double FnY = FyG + FyC;

    s2->acceleration.x = FnX/s2->mass;
    s2->acceleration.y = FnY/s2->mass;

    s2->position.x = 0.5 * s2->acceleration.x * frame * frame + s2->velocity.x * frame + s2->position.x;
    s2->position.y = 0.5 * s2->acceleration.y * frame * frame + s2->velocity.y * frame + s2->position.y;

    s2->velocity.x = s2->velocity.x + s2->acceleration.x * frame;
    s2->velocity.y = s2->velocity.y + s2->acceleration.y * frame;

    std::cout << s2->acceleration.x << std::endl;
    std::cout << s2->acceleration.y << std::endl;
    s2->Draw(renderer);
}